#ifndef NURSINGROBOT_RRT_HPP
#define NURSINGROBOT_RRT_HPP
#include "planner/Tree.hpp"
#include <random>

namespace planner {


    template<typename T,typename Distance>
    class RRT;

    template<typename T,typename Distance =flann::L1<double>>
    struct PLAN_REQUEST {
    public:
        PLAN_REQUEST(const T &start, const T &goal, double time_limit = 5,
                     double step_len = 0.05, bool is_step_relative = false,
                     double max_goal_dist = 0.05,double goal_bias = 0.1)
                : _start(start),
                  _goal(goal),
                  _time_limit(time_limit),
                  _step_len(step_len),
                  _is_step_relative(is_step_relative),
                  _max_goal_dist(max_goal_dist),
                  _goal_bias(goal_bias)
        {

        };

        friend RRT<T,Distance>;
    private:
        T _start;
        T _goal;
        double _time_limit;
        double _step_len;
        double _max_goal_dist;
        bool _is_step_relative;
        double _goal_bias;
    };

    template<typename T,typename Distance>
    class RRT {
    protected:
        std::shared_ptr<Tree<T,Distance>> _tree_ptr;

        Vertex <T> *_tail;

        T _start,_goal;

        bool _isPlanConstructed{false};

        const std::size_t _dimensions;

        std::size_t _iter_max{};

        std::size_t _total_nodes{1};

        double _step_len{};

        bool _is_step_relative{false};

        double _goal_bias{};

        double _goal_max_dist{};

        double _d_min{};

        double _time_limit{};

        const Eigen::MatrixX2d *_bounds_ptr;

        std::function<bool(const T &, const T &)> _state_validate_func;


        virtual Vertex <T> *_steer(std::shared_ptr<Tree<T,Distance>> & tree_ptr,const T &rand_state, Vertex <T> *source, bool check_collision)
        {
            Vertex<T> * nearest_vertex{source};
            if (!nearest_vertex) {
                nearest_vertex= tree_ptr->nearest(rand_state, nullptr);
                if (nearest_vertex == nullptr) return nullptr;
            }

            //consider a non-relative step 0.05
            T intermediate_state = planner::extend(nearest_vertex->state(), rand_state, _step_len);
            if (!_isStateValid(nearest_vertex->state(), intermediate_state, check_collision)) return nullptr;
            tree_ptr->addState(intermediate_state,nearest_vertex);
            return tree_ptr->LastVertex();
        }

        bool _isReached(const Vertex <T> *node_end, const T& goal, bool check_collision = true )
        {
            bool near = _is_step_relative ? planner::distance(node_end->state(), _goal) / _d_min < _goal_max_dist :
                        planner::distance(node_end->state(), goal) <= _goal_max_dist;
            near = near ? _isStateValid(node_end->state(), goal, check_collision) : near;
            return near;
        };

        virtual T _sample()
        {
            return randomState<T>(_dimensions, _bounds_ptr);
        }

        virtual bool _isStateValid(const T &from, const T &to, bool check_collision)
        {
            if (_state_validate_func && check_collision)
                return _state_validate_func(from, to);
            else
                return _state_validate_func(to,to);
        };


        virtual bool argsCheck()
        {
            if (_is_step_relative && (_step_len > 1 || _step_len < 0)) {
                std::cout
                        << "receive relative step request while have step len or max step len not match the range of [0,1]" <<std::endl;
                return false;
            }
            if (_goal_bias < 0 || _goal_bias > 1) {
                std::cout << "The goal bias must be a number between 0.0 and 1.0" <<std::endl;
                return false;
            }
            return true;
        }

    public:

        RRT(const RRT<T,Distance> &) = delete;

        RRT &operator=(const RRT<T,Distance> &) = delete;

        explicit RRT(std::size_t dimensions,
            std::function<T(typename Distance::ElementType *)> arrayToT = NULL,
            std::function<void(const T&, typename Distance::ElementType *)> TToArray = NULL)
            :_tree_ptr(std::make_shared<Tree<T,Distance>>(dimensions,arrayToT,TToArray)),
            _bounds_ptr(nullptr),
            _dimensions(dimensions)
        {
            setStepLen(0.1);
            setMaxIterations(1e9);
            setGoalBias(0.05);
            setGoalMaxDist(_step_len);
        };

        virtual ~RRT() = default;

        std::size_t MaxIterations() const
        { return _iter_max; };

        void setMaxIterations(std::size_t itr)
        { _iter_max = itr; };


        double GoalBias() const
        { return _goal_bias; };

        void setGoalBias(double goalBias)
        {
            _goal_bias = goalBias;
        };

        double StepLen() const
        { return _step_len; }

        void setStepLen(double stepSize, bool isRelative = false)
        {
            _step_len = stepSize;
            _is_step_relative = isRelative;
        }

        bool isStepRelative() const
        { return _is_step_relative; }

        double GoalMaxDist() const
        { return _goal_max_dist; }

        void setGoalMaxDist(double maxDist)
        { _goal_max_dist = maxDist; }


        void setStateValidator(std::function<bool(const T &, const T &)> state_validate_func)
        {
            _state_validate_func = state_validate_func;
        }

        T GoalState() const
        { return _goal; }

        void setGoalState(const T &goalState)
        {
            _goal = goalState;
        }

        T StartState() const
        { return _start; }

        void setStartState(const T &startState)
        {
            _start = startState;
            _tree_ptr->setStartState(startState);
        }

        Eigen::MatrixX2d SampleBounds() const
        { return *_bounds_ptr; }

        void setSampleBounds(const Eigen::MatrixX2d *bounds_ptr){
            delete _bounds_ptr;
            _bounds_ptr = bounds_ptr;
        }


        virtual void constructPlan(const PLAN_REQUEST<T,Distance> &rrtRequest)
        {
            if (_isStateValid(rrtRequest._start, rrtRequest._start, true) &&
                _isStateValid(rrtRequest._goal, rrtRequest._goal, true)) {
                setStartState(rrtRequest._start);
                setGoalState(rrtRequest._goal);
                _step_len = rrtRequest._step_len;
                _goal_max_dist = rrtRequest._max_goal_dist;
                _is_step_relative = rrtRequest._is_step_relative;
                _d_min = planner::distance(rrtRequest._start, rrtRequest._goal);
                _time_limit = rrtRequest._time_limit;
                _goal_bias = rrtRequest._goal_bias;
                _isPlanConstructed = true;
            } else
                std::cout << "Start or goal is not valid, please reset"<<std::endl;
        }

        virtual bool planning()
        {
            // validity check
            if (!_isPlanConstructed|| !argsCheck())
                return false;
            //when start state is near goal, check is the path valid
            if ((!_is_step_relative && _isReached(_tree_ptr->RootVertex(),_goal))
                || _is_step_relative && _d_min <= std::numeric_limits<double>::epsilon()) {
                _tree_ptr->addState(_goal,_tree_ptr->RootVertex());
                _tail = _tree_ptr->LastVertex();
                return true;
            }

            time_t start{clock()};
            double time{};
            for (int i = 0; i < _iter_max; ++i) {
                time = (double) (clock() - start) / CLOCKS_PER_SEC;
                if (time >= _time_limit) {
                    std::cout << "No path find within " << _time_limit << " seconds"
                               << " now iterates " << i << "times"<<std::endl;
                    this->_total_nodes = this->_tree_ptr->TreeSize();
                    return false;
                }
                Vertex<T> *new_vertex;

                double r = fabs(planner::randomState<state_space::Rn>(1, nullptr)[0]);

                if (r < _goal_bias)
                    new_vertex = _steer(_tree_ptr,_goal, nullptr, true);
                else
                    new_vertex = _steer(_tree_ptr,_sample(), nullptr, true);
                if (new_vertex && _isReached(new_vertex,_goal)) {
                    _tree_ptr->addState(_goal,new_vertex);
                    _tail = _tree_ptr->LastVertex();
                    this->_total_nodes = this->_tree_ptr->TreeSize();
                    return true;
                }
            }
            this->_total_nodes = this->_tree_ptr->TreeSize();
            std::cout << "No path find within " << _iter_max << " iterations"<<std::endl;
            return false;
        }

        virtual std::vector<T> GetPath()
        {
            std::vector<T> path;
            _tree_ptr->extract_path(path,_tail,false);
            return path;
        }
        virtual std::string getName() const{
            return "RRT_Simple";
        }
        virtual std::size_t getTotalNodes() const{
            return _total_nodes;
        };
        virtual std::vector<Vertex<T>*> getRootVertex()
        {
            std::vector<Vertex<T>*> results;
            results.template emplace_back(_tree_ptr->RootVertex());
            return results;
        }
    };


}


#endif //NURSINGROBOT_RRT_HPP
