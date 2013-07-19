#ifndef CGAL_KD_KERNEL_D_INTERFACE_H
#define CGAL_KD_KERNEL_D_INTERFACE_H

#include <CGAL/functor_tags.h>
#include <CGAL/transforming_iterator.h>
#include <CGAL/marcutils.h>
#include <CGAL/tuple.h>


namespace CGAL {
template <class Base_> struct Kernel_d_interface : public Base_ {
  CGAL_CONSTEXPR Kernel_d_interface(){}
  CGAL_CONSTEXPR Kernel_d_interface(int d):Base_(d){}

	typedef Base_ Base;
	typedef Kernel_d_interface<Base> Kernel;
	typedef Base_ R_; // for the macros
	typedef typename Get_type<Base, RT_tag>::type RT;
	typedef typename Get_type<Base, FT_tag>::type FT;
	typedef typename Get_type<Base, Bool_tag>::type Boolean;
	typedef typename Get_type<Base, Sign_tag>::type Sign;
	typedef typename Get_type<Base, Comparison_result_tag>::type Comparison_result;
	typedef typename Get_type<Base, Orientation_tag>::type Orientation;
	typedef typename Get_type<Base, Oriented_side_tag>::type Oriented_side;
	typedef typename Get_type<Base, Bounded_side_tag>::type Bounded_side;
	typedef typename Get_type<Base, Angle_tag>::type Angle;
	typedef typename Get_type<Base, Flat_orientation_tag>::type Flat_orientation_d;
	typedef typename Get_type<Base, Point_tag>::type	Point_d;
	typedef typename Get_type<Base, Vector_tag>::type	Vector_d;
	typedef typename Get_type<Base, Segment_tag>::type	Segment_d;
	typedef typename Get_type<Base, Sphere_tag>::type	Sphere_d;
	typedef typename Get_type<Base, Hyperplane_tag>::type	Hyperplane_d;
	typedef Vector_d Direction_d;
	typedef typename Get_type<Base, Line_tag>::type	Line_d;
	typedef typename Get_type<Base, Ray_tag>::type	Ray_d;
	typedef typename Get_type<Base, Iso_box_tag>::type	Iso_box_d;
	typedef typename Get_type<Base, Aff_transformation_tag>::type	Aff_transformation_d;
	typedef typename Get_functor<Base, Compute_point_cartesian_coordinate_tag>::type Compute_coordinate_d;
	typedef typename Get_functor<Base, Compare_lexicographically_tag>::type Compare_lexicographically_d;
	typedef typename Get_functor<Base, Equal_points_tag>::type Equal_d;
	typedef typename Get_functor<Base, Less_lexicographically_tag>::type Less_lexicographically_d;
	typedef typename Get_functor<Base, Less_or_equal_lexicographically_tag>::type Less_or_equal_lexicographically_d;
	// FIXME: and vectors?
	typedef typename Get_functor<Base, Orientation_of_points_tag>::type Orientation_d;
	typedef typename Get_functor<Base, Less_point_cartesian_coordinate_tag>::type Less_coordinate_d;
	typedef typename Get_functor<Base, Point_dimension_tag>::type Point_dimension_d;
	typedef typename Get_functor<Base, Side_of_oriented_sphere_tag>::type Side_of_oriented_sphere_d;
	typedef typename Get_functor<Base, Contained_in_affine_hull_tag>::type Contained_in_affine_hull_d;
	typedef typename Get_functor<Base, Construct_flat_orientation_tag>::type Construct_flat_orientation_d;
	typedef typename Get_functor<Base, In_flat_orientation_tag>::type In_flat_orientation_d;
	typedef typename Get_functor<Base, In_flat_side_of_oriented_sphere_tag>::type In_flat_side_of_oriented_sphere_d;
	typedef typename Get_functor<Base, Point_to_vector_tag>::type Point_to_vector_d;
	typedef typename Get_functor<Base, Vector_to_point_tag>::type Vector_to_point_d;
	typedef typename Get_functor<Base, Construct_ttag<Point_tag> >::type Construct_point_d;
	typedef typename Get_functor<Base, Construct_ttag<Vector_tag> >::type Construct_vector_d;
	typedef typename Get_functor<Base, Construct_ttag<Segment_tag> >::type Construct_segment_d;
	typedef typename Get_functor<Base, Construct_ttag<Sphere_tag> >::type Construct_sphere_d;
	typedef typename Get_functor<Base, Construct_ttag<Hyperplane_tag> >::type Construct_hyperplane_d;
	typedef Construct_vector_d Construct_direction_d;
	typedef typename Get_functor<Base, Construct_ttag<Line_tag> >::type Construct_line_d;
	typedef typename Get_functor<Base, Construct_ttag<Ray_tag> >::type Construct_ray_d;
	typedef typename Get_functor<Base, Construct_ttag<Iso_box_tag> >::type Construct_iso_box_d;
	typedef typename Get_functor<Base, Construct_ttag<Aff_transformation_tag> >::type Construct_aff_transformation_d;
	typedef typename Get_functor<Base, Midpoint_tag>::type Midpoint_d;
	struct Component_accessor_d : private Store_kernel<R_> {
	  CGAL_FUNCTOR_INIT_STORE(Component_accessor_d)
	  int dimension(Point_d const&p){
	    return this->kernel().point_dimension_d_object()(p);
	  }
	  FT cartesian(Point_d const&p, int i){
	    return this->kernel().compute_coordinate_d_object()(p);
	  }
	  RT homogeneous(Point_d const&p, int i){
	    throw "not implemented yet";
	    return 0;
	    // FIXME
	    //return this->kernel().compute_coordinate_d_object()(p);
	  }
	};
	struct Construct_cartesian_const_iterator_d : private Store_kernel<R_> {
	  CGAL_FUNCTOR_INIT_STORE(Construct_cartesian_const_iterator_d)
	  typedef typename Get_functor<Base, Construct_ttag<Point_cartesian_const_iterator_tag> >::type CPI;
	  typedef typename Get_functor<Base, Construct_ttag<Point_cartesian_const_iterator_tag> >::type CVI;
	  typedef typename CGAL::decay<typename boost::result_of<CPI(Point_d,CGAL::Begin_tag)>::type>::type result_type;
	  // Kernel_d requires a common iterator type for points and vectors
	  // TODO: provide this mixed functor in preKernel?
	  CGAL_static_assertion((boost::is_same<typename CGAL::decay<typename boost::result_of<CVI(Vector_d,CGAL::Begin_tag)>::type>::type, result_type>::value));
	  template <class Tag_>
	  result_type operator()(Point_d const&p, Tag_ t)const{
	    return CPI(this->kernel())(p,t);
	  }
	  template <class Tag_>
	  result_type operator()(typename First_if_different<Vector_d,Point_d>::Type const&v, Tag_ t)const{
	    return CVI(this->kernel())(v,t);
	  }

	  template <class Obj>
	  result_type operator()(Obj const&o)const{
	    return operator()(o, Begin_tag());
	  }
	  result_type operator()(Point_d const&p, int)const{
	    return operator()(p, End_tag());
	  }
	  result_type operator()(typename First_if_different<Vector_d,Point_d>::Type const&v, int)const{
	    return operator()(v, End_tag());
	  }
	};
	typedef typename Construct_cartesian_const_iterator_d::result_type Cartesian_const_iterator_d;
	typedef typename Get_functor<Base, Squared_distance_tag>::type Squared_distance_d;
	//typedef typename Get_functor<Base, Affine_rank_tag>::type Affine_rank_d;
	//typedef typename Get_functor<Base, Affinely_independent_tag>::type Affinely_independent_d;
	//typedef typename Get_functor<Base, Contained_in_linear_hull_tag>::type Contained_in_linear_hull_d;
	//typedef typename Get_functor<Base, Contained_in_simplex_tag>::type Contained_in_simplex_d;
	//typedef typename Get_functor<Base, Has_on_positive_side_tag>::type Has_on_positive_side_d;
	//typedef typename Get_functor<Base, Linear_rank_tag>::type Linear_rank_d;
	//typedef typename Get_functor<Base, Linearly_independent_tag>::type Linearly_independent_d;
	//typedef typename Get_functor<Base, Oriented_side_tag>::type Oriented_side_d;
	//typedef typename Get_functor<Base, Side_of_bounded_sphere_tag>::type Side_of_bounded_sphere_d;

	//typedef typename Get_functor<Base, Center_of_sphere_tag>::type Center_of_sphere_d;
	//typedef typename Get_functor<Base, Value_at_tag>::type Value_at_d;
	//typedef typename Get_functor<Base, Point_of_sphere_tag>::type Point_of_sphere_d;
	typedef typename Get_functor<Base, Orthogonal_vector_tag>::type Orthogonal_vector_d;
	//typedef typename Get_functor<Base, Linear_base_tag>::type Linear_base_d;

	//typedef ??? Intersect_d;


	Compute_coordinate_d compute_coordinate_d_object()const{ return Compute_coordinate_d(*this); }
	Compare_lexicographically_d compare_lexicographically_d_object()const{ return Compare_lexicographically_d(*this); }
	Equal_d equal_d_object()const{ return Equal_d(*this); }
	Less_lexicographically_d less_lexicographically_d_object()const{ return Less_lexicographically_d(*this); }
	Less_or_equal_lexicographically_d less_or_equal_lexicographically_d_object()const{ return Less_or_equal_lexicographically_d(*this); }
	Less_coordinate_d less_coordinate_d_object()const{ return Less_coordinate_d(*this); }
	Orientation_d orientation_d_object()const{ return Orientation_d(*this); }
	Point_dimension_d point_dimension_d_object()const{ return Point_dimension_d(*this); }
	Side_of_oriented_sphere_d side_of_oriented_sphere_d_object()const{ return Side_of_oriented_sphere_d(*this); }
	Contained_in_affine_hull_d contained_in_affine_hull_d_object()const{ return Contained_in_affine_hull_d(*this); }
	Construct_flat_orientation_d construct_flat_orientation_d_object()const{ return Construct_flat_orientation_d(*this); }
	In_flat_orientation_d in_flat_orientation_d_object()const{ return In_flat_orientation_d(*this); }
	In_flat_side_of_oriented_sphere_d in_flat_side_of_oriented_sphere_d_object()const{ return In_flat_side_of_oriented_sphere_d(*this); }
	Point_to_vector_d point_to_vector_d_object()const{ return Point_to_vector_d(*this); }
	Vector_to_point_d vector_to_point_d_object()const{ return Vector_to_point_d(*this); }
	Midpoint_d midpoint_d_object()const{ return Midpoint_d(*this); }
	Component_accessor_d component_accessor_d_object()const{ return Component_accessor_d(*this); }
	Orthogonal_vector_d orthogonal_vector_d_object()const{ return Orthogonal_vector_d(*this); }
	Construct_cartesian_const_iterator_d construct_cartesian_const_iterator_d_object()const{ return Construct_cartesian_const_iterator_d(*this); }
	Construct_point_d construct_point_d_object()const{ return Construct_point_d(*this); }
	Construct_vector_d construct_vector_d_object()const{ return Construct_vector_d(*this); }
	Construct_segment_d construct_segment_d_object()const{ return Construct_segment_d(*this); }
	Construct_sphere_d construct_sphere_d_object()const{ return Construct_sphere_d(*this); }
	Construct_hyperplane_d construct_hyperplane_d_object()const{ return Construct_hyperplane_d(*this); }
	Squared_distance_d squared_distance_d_object()const{ return Squared_distance_d(*this); }
	Construct_direction_d construct_direction_d_object()const{ return Construct_direction_d(*this); }
	Construct_line_d construct_line_d_object()const{ return Construct_line_d(*this); }
	Construct_ray_d construct_ray_d_object()const{ return Construct_ray_d(*this); }
	Construct_iso_box_d construct_iso_box_d_object()const{ return Construct_iso_box_d(*this); }
	Construct_aff_transformation_d construct_aff_transformation_d_object()const{ return Construct_aff_transformation_d(*this); }

	// Dummies for those required functors missing a concept.
	typedef Null_functor Position_on_line_d;
	Position_on_line_d position_on_line_d_object()const{return Null_functor();}
	typedef Null_functor Barycentric_coordinates_d;
	Barycentric_coordinates_d barycentric_coordinates_d_object()const{return Null_functor();}

	/* Not provided because they don't make sense here:
	   Lift_to_paraboloid_d
	   Project_along_d_axis_d
	 */
};
}

#endif // CGAL_KD_KERNEL_D_INTERFACE_H
