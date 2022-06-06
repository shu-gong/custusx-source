/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2012, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Willow Garage nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/
/* copied from moveit source/moveit_core/macros/class_forward*/

/* Author: Ioan Sucan */
#ifndef NURSINGROBOT_CLASS_FORWARD_H
#define NURSINGROBOT_CLASS_FORWARD_H

#include <memory>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <forward_list>

#define DECLARE_SEQUENTIAL_CONTAINER(Name, Type)                                                                       \
  typedef std::vector<Type, Eigen::aligned_allocator<Type> >  vector_##Name;                                             \
  typedef std::deque<Type,  Eigen::aligned_allocator<Type>>   deque_##Name;                                              \
  typedef std::list<Type,   Eigen::aligned_allocator<Type>>    list_##Name;                                               \
  typedef std::forward_list<Type,   Eigen::aligned_allocator<Type>> forward_list_##Name;

#define DECLARE_NO_ALIGN_SEQUENTIAL_CONTAINER(Name, Type)                                                                       \
  typedef std::vector<Type>  vector_##Name;                                             \
  typedef std::deque<Type>   deque_##Name;                                              \
  typedef std::list<Type>    list_##Name;                                               \
  typedef std::forward_list<Type> forward_list_##Name;
/**
 * \def MOVEIT_DELCARE_PTR
 * Macro that given a Name and a Type declares the following types:
 * - ${Name}Ptr            = shared_ptr<${Type}>
 * - ${Name}ConstPtr       = shared_ptr<const ${Type}>
 * - ${Name}WeakPtr        = weak_ptr<${Type}>
 * - ${Name}ConstWeakPtr   = weak_ptr<const ${Type}>
 * - ${Name}UniquePtr      = unique_ptr<${Type}>
 * - ${Name}ConstUniquePtr = unique_ptr<const ${Type}>
 *
 * For best portability the exact type of shared_ptr declared by the macro
 * should be considered to be an implementation detail, liable to change in
 * future releases.
 */

#define MOVEIT_DECLARE_PTR(Name, Type)                                                                                 \
  typedef std::shared_ptr<Type> Name##Ptr;                                                                             \
  typedef std::shared_ptr<const Type> Name##ConstPtr;                                                                  \
  typedef std::weak_ptr<Type> Name##WeakPtr;                                                                           \
  typedef std::weak_ptr<const Type> Name##ConstWeakPtr;                                                                \
  typedef std::unique_ptr<Type> Name##UniquePtr;                                                                       \
  typedef std::unique_ptr<const Type> Name##ConstUniquePtr;

/**
 * \def MOVEIT_DELCARE_PTR_MEMBER
 * The macro defines the same typedefs as MOVEIT_DECLARE_PTR, but shortens the new names to their suffix.
 *
 * This can be used to create `Classname::Ptr` style names, but in most situations in MoveIt's codebase,
 * MOVEIT_CLASS_FORWARD and MOVEIT_DECLARE_PTR should be preferred.
 */

#define MOVEIT_DECLARE_PTR_MEMBER(Type)                                                                                \
  typedef std::shared_ptr<Type> Ptr;                                                                                   \
  typedef std::shared_ptr<const Type> ConstPtr;                                                                        \
  typedef std::weak_ptr<Type> WeakPtr;                                                                                 \
  typedef std::weak_ptr<const Type> ConstWeakPtr;                                                                      \
  typedef std::unique_ptr<Type> UniquePtr;                                                                             \
  typedef std::unique_ptr<const Type> ConstUniquePtr;

/**
 * \def MOVEIT_CLASS_FORWARD
 * Macro that forward declares a class and defines the respective smartpointers through MOVEIT_DECLARE_PTR.
 */

#define MOVEIT_CLASS_FORWARD(C)                                                                                        \
  class C;                                                                                                             \
  MOVEIT_DECLARE_PTR(C, C);

/**
 * \def MOVEIT_STRUCT_FORWARD
 * Like MOVEIT_CLASS_FORWARD, but forward declares the type as a struct
 * instead of a class.
 */
#define MOVEIT_STRUCT_FORWARD(C)                                                                                       \
  struct C;                                                                                                            \
  MOVEIT_DECLARE_PTR(C, C);
/***
 *\def check;
 */
#define ALIGNED_CLASS_STL_FORWARD(C)                                                                                   \
  class C;                                                                                                             \
  DECLARE_SEQUENTIAL_CONTAINER(C, C);

#define DONT_ALIGN_CLASS_STL_FORWARD(C)                                                                               \
  class C;                                                                                                             \
  DECLARE_NO_ALIGN_SEQUENTIAL_CONTAINER(C,C);


#endif //NURSINGROBOT_CLASS_FORWARD_H
