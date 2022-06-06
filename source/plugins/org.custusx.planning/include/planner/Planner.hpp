//
// Created by xcy on 2020/12/14.
//

#ifndef NURSINGROBOT_PLANNER_HPP
#define NURSINGROBOT_PLANNER_HPP

#include <utility>

#include "../StateSpace/SE3.hpp"
#include "../StateSpace/SO3.hpp"
#include "../StateSpace/rn.hpp"
#include <unordered_map>
#include <deque>
#include <flann/flann.hpp>
#include <flann/algorithms/dist.h>
#include <flann/algorithms/kdtree_single_index.h>
#include <stdexcept>
#include <type_traits>
#include <functional>
#include <cstdlib>
#include <list>
#include "boost/functional/hash.hpp"
namespace planner {
    enum PLANNER_TYPE {
        RRT_SIMPLE,
        RRT_CONNECT,
        LAZY_RRT_CONNECT,
        LAZY_RRT,
        RRT_STAR,
        INFORMED_RRT_STAR
    };
    /**
     *
     * @tparam T
     * @param state
     * @return hash function for state
     */
    template<typename T>
    static size_t hash(T state)
    {
        size_t seed = 0;
        for (int i = 0; i < state.Vector().size(); ++i) {
            boost::hash_combine(seed, state.Vector()[i]);
        }
        return seed;
    }

    template<typename T>
    static T randomState(int dimensions = -1, const Eigen::MatrixX2d *bounds_ptr = nullptr)
    {
        static std::random_device rd;
        static std::default_random_engine randomEngine(rd());
        if (bounds_ptr != nullptr && bounds_ptr->rows() != dimensions) {
            throw std::invalid_argument("dimensions and bounds are not equal!");
        }
        return dimensions == -1 ? T::Zero().random(randomEngine, bounds_ptr) : T::Zero(dimensions).random(randomEngine,
                                                                                                          bounds_ptr);
    }

    template<>
    state_space::SE3 randomState(int dimensions, const Eigen::MatrixX2d *bounds_ptr)
    {
        static std::random_device rd;
        static std::default_random_engine randomEngine(rd());
        if (bounds_ptr != nullptr && bounds_ptr->rows() != 3) {
            throw std::invalid_argument("only bound translation part");
        }
        return state_space::SE3::Zero().random(randomEngine, bounds_ptr);
    }

    /**
     * Finds a state in the direction of @target from @source.state().
     * @param lambda The relative normalized distance from @source, which must
     * inside the range of [0,1]
     *
     * @return A state in the direction of @target from @source (hyper linear interpolation)
     */
    template<typename T>
    static T interpolate(const T &source, const T &target,
                         double lambda)
    {
        if (lambda > 1 || lambda < 0) {
            throw std::invalid_argument
                    ("only interpolate state with [source, target], please use 'extend' function \n");
        }
        return source + (target - source) * lambda;
    }

    /**
     * Gets a state in the direction of @source to @target, with a distance from @source
     * @param extend_length the distance of return state from @source
     * @return A state
     */
    template<typename T>
    static T extend(const T &source, const T &target, double extend_length)
    {
        if(source == target)
            return target;
        T extend_direction = target - source;
        extend_direction = extend_direction * (1.0 / extend_direction.norm());
        return source + (extend_direction * extend_length);
    }

    /**
     * An overloaded version designed for bezier interpolation
     *
     * @param source The start state
     * @param target The point in the space to extend to
     * @param lambda The relative normalized distance from @source, which must
     * inside the range of [0,1]
     *
     * @return A state in the bezier curve of @target from @source.state(), the control points are fixed
     * and divided equally.
     */
    template<typename T>
    static T bezierInterpolate(const T &source, const T &target, double lambda)
    {
        T delta = target - source;
        T result;
        result = source * (1 * pow(lambda, 0) * pow((1 - lambda), 5 - 0)) +
                 (source - delta * 2) * (5 * pow(lambda, 1) * pow((1 - lambda), 5 - 1)) +
                 (source - delta) * (10 * pow(lambda, 2) * pow((1 - lambda), 5 - 2)) +
                 (source + delta * 3) * (10 * pow(lambda, 3) * pow((1 - lambda), 5 - 3)) +
                 (source + delta * 2) * (5 * pow(lambda, 4) * pow((1 - lambda), 5 - 4)) +
                 target * (1 * pow(lambda, 5) * pow((1 - lambda), 5 - 5));
        return result;
    }

    /**
     * \brief compact interpolate for SE3
     * */
    static state_space::SE3 sphereInterpolate(const state_space::SE3 &source,
                                              const state_space::SE3 &target,
                                              double lambda)
    {
        auto temp_translation = interpolate(source.translationPart(), target.translationPart(), lambda);
        auto temp_SO3 = interpolate(source.SO3Part(),target.SO3Part(),lambda);
        return {temp_SO3, temp_translation};
    }

    static state_space::SE3 combinedInterpolate(const state_space::SE3 &source,
                                                const state_space::SE3 &target,
                                                double lambda)
    {
        auto temp_translation = interpolate(source.translationPart(), target.translationPart(), lambda);
        auto temp_SO3 = bezierInterpolate(source.SO3Part(),target.SO3Part(),lambda);
        return {temp_SO3, temp_translation};
    }

    /**
     * @brief Calculate the distance between two states
     *
     * @param from Start state
     * @param to End state
     *
     * @return The distance between the states
     */
    template<typename T>
    double distance(const T &from, const T &to)
    {
        return from.distance(to);
    }


    /**
     * @brief Calculate the control points smoothing the give states contained in @state_list
     *
     * @param state_list containing all states needed to be smoothed
     *
     * @return a vector contains all six control points for each segment.
     */
    //TODO: Not implemented
    template<typename T>
    std::vector<std::array<T, 6>> getBezierControlPoints(const std::vector<T> &state_list)
    {
        std::vector<std::array<T, 6>> control_points_list{};
        return control_points_list;
    }

    template<typename T>
    class Vertex {
    public:

        explicit Vertex(const T &data, Vertex<T> * parent = nullptr, int dimensions = 6,
                        std::function<void(T, double *)> TToArray = NULL)
                : _state(data), _parent(parent)
        {
            _vec.resize(dimensions);
            if (_parent) {
                _parent->_children.push_back(this);
            }
            if (NULL == TToArray) {
                memcpy(_vec.data(), data.data(), dimensions * sizeof(double));
            } else {
                TToArray(data, _vec.data());
            }
        };

        explicit Vertex()
                : _state(T::Zero()),
                  _vec(std::vector<double>()),
                  _parent(nullptr),
                  _children(std::list<Vertex<T> *>())
        {

        }

        Vertex<T>* parent() const
        { return _parent; };

        Vertex<T>* &parent()
        {return _parent;}

        int depth() const
        {
            int n = 0;
            Vertex<T> *ancestor = _parent;
            while (ancestor != nullptr) {
                n++;
                ancestor = ancestor->_parent;
            }
            return n;
        };

        const T &state() const
        { return _state; };

        double *data() const
        { return const_cast<double *>(_vec.data()); };

        std::list<Vertex<T> *> & children()
        {
            return _children;
        }
    private:
        std::vector<double> _vec;
        T _state;
        Vertex *_parent;
        std::list<Vertex<T> *> _children;
    };


}


#endif //NURSINGROBOT_PLANNER_HPP
