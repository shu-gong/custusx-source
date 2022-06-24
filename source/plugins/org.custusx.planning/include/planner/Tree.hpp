#ifndef NURSINGROBOT_TREE_HPP
#define NURSINGROBOT_TREE_HPP

#include "../planner/Planner.hpp"

namespace planner {

    template<typename T, typename Distance>
    class Tree {
    protected:
        std::deque<Vertex < T>> _nodes;

        std::size_t _dimensions;

        std::shared_ptr<flann::Index<Distance>> _kd_tree{};

        std::function<T(typename Distance::ElementType *)> _arrayToT;

        std::function<void(const T&, typename Distance::ElementType *)> TToArray_;

    public:
        Tree(const Tree<T, Distance> &) = default;

        Tree &operator=(const Tree<T, Distance> &) = default;

        explicit Tree(std::size_t dimensions,
             std::function<T(typename Distance::ElementType *)> arrayToT = NULL,
             std::function<void(const T&, typename Distance::ElementType *)> TToArray = NULL)
                : _dimensions(dimensions),
                  _kd_tree(std::make_shared<flann::Index<Distance>>(flann::KDTreeSingleIndexParams())),
                  _arrayToT(arrayToT),
                  TToArray_(TToArray) {

        };

        virtual ~Tree() = default;

        //return the root of the tree
        Vertex <T> *RootVertex() {
            if (_nodes.empty()) return nullptr;

            return &_nodes.front();
        }

        Vertex <T> *LastVertex() {
            if (_nodes.empty()) return nullptr;

            return &_nodes.back();
        }

        Vertex<T> * fetchState(std::size_t index){
            return &*(_nodes.begin() + index);
        }

        std::size_t TreeSize() const {
            return _nodes.size();
        }

        void reset(bool eraseRoot = false) {
            _kd_tree.reset(new flann::Index<Distance>(flann::KDTreeSingleIndexParams()));
            if (eraseRoot) {
                _nodes.clear();
            } else if (_nodes.size() > 1) {
                //clear all node but left root
                T root = RootVertex()->state();
                _nodes.clear();
                _nodes.template emplace_back(root, nullptr, _dimensions, TToArray_);
                _kd_tree->buildIndex(flann::Matrix<typename Distance::ElementType>(RootVertex()->data(), 1, _dimensions));
            }
        };

        void setStartState(const T &startState) {
            reset(true);
            // create root node from provided start state
            _nodes.template emplace_back(startState, nullptr, _dimensions, TToArray_);
            _kd_tree->buildIndex(flann::Matrix<typename Distance::ElementType>(RootVertex()->data(), 1, _dimensions));
        };

        virtual Vertex <T> *nearest(const T &current_state, typename Distance::ElementType *distance_out) {
            //K-NN search
            std::vector<typename Distance::ElementType> data(_dimensions);
            flann::Matrix<typename Distance::ElementType> query;
            if (NULL == TToArray_) {
                memcpy(data.data(), current_state.data(), _dimensions * sizeof(typename Distance::ElementType));
                query = flann::Matrix<typename Distance::ElementType>(data.data(), 1, _dimensions);
            } else {
                TToArray_(current_state, data.data());
                query = flann::Matrix<typename Distance::ElementType>(data.data(), 1, _dimensions);
            }
            std::vector<std::vector<size_t>> indices(1);
            std::vector<std::vector<typename Distance::ElementType>> dists(1);
            _kd_tree->knnSearch(query, indices, dists, 1, flann::SearchParams());
            if (distance_out)
                *distance_out = dists[0][0];
            return &(*(_nodes.begin() + indices[0][0]));
        };

        virtual void addState(const T &state, Vertex <T> *parent) {
            _nodes.template emplace_back(state, parent, _dimensions, TToArray_);
            _kd_tree->addPoints(flann::Matrix<typename Distance::ElementType>(_nodes.back().data(), 1, _dimensions));
        };


        void extract_path_ptr(std::vector<Vertex < T> *> &vertex_vector, Vertex <T> *tail){
            vertex_vector.clear();
            Vertex <T> *vertex = tail;
            while (vertex) {
                vertex_vector.template emplace_back(vertex);
                vertex = vertex->parent();
            }
        };

        void extract_path_impl(std::vector<T> &vectorOut, const std::vector<Vertex < T> *> &vertex_vector, bool reverse){
            if (reverse) {
                for (auto itr = vertex_vector.begin(); itr != vertex_vector.end(); itr++) {
                    vectorOut.template emplace_back((*itr)->state());
                }
            } else {
                for (auto itr = vertex_vector.rbegin(); itr != vertex_vector.rend(); itr++) {
                    vectorOut.template emplace_back((*itr)->state());
                }
            }
        };

        virtual void extract_path(std::vector<T> &vectorOut, Vertex <T> *tail, bool reverse) {
            vectorOut.clear();
            std::vector<Vertex<T> *> vertex_vector;
            extract_path_ptr(vertex_vector, tail);
            extract_path_impl(vectorOut, vertex_vector, reverse);
        };
    };
}


#endif //NURSINGROBOT_TREE_HPP
