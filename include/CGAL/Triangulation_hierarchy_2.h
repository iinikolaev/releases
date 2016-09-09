// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/Triangulation_hierarchy_2.h
// package       : Triangulation (4.69)
// source        : $RCSfile: Triangulation_hierarchy_2.h,v $
// revision      : 
// revision_date : 
// author(s)     : Olivier Devillers
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef TRIANGULATION_HIERARCHY_2_H
#define TRIANGULATION_HIERARCHY_2_H

#include <CGAL/Random.h>

CGAL_BEGIN_NAMESPACE

template < class Vbb>
class Triangulation_hierarchy_vertex_base_2
 : public Vbb
{
 public:
  typedef Vbb V_Base;
  typedef typename V_Base::Point   Point;


  Triangulation_hierarchy_vertex_base_2()
    : V_Base(), _up(0), _down(0)
    {}
  Triangulation_hierarchy_vertex_base_2(const Point & p, void* f)
    : V_Base(p,f), _up(0), _down(0)
    {}
  Triangulation_hierarchy_vertex_base_2(const Point & p)
    : V_Base(p), _up(0), _down(0)
    {}

 public:  // for use in Triangulation_hierarchy only
  //  friend class Triangulation_hierarchy_2;
  void* up() {return _up;}
  void* down() {return _down;}
  void set_up(void *u) {_up=u;}
  void set_down(void *d) {if (this) _down=d;}


 private:
  void* _up;    // same vertex one level above
  void* _down;  // same vertex one level below
};

// parameterization of the  hierarchy
const float Triangulation_hierarchy_2__ratio    = 30.0;
const int   Triangulation_hierarchy_2__minsize  = 20;
const int   Triangulation_hierarchy_2__maxlevel = 5;
// maximal number of points is 30^5 = 24 millions !

template < class Tr>
class Triangulation_hierarchy_2
: public Tr
{
 public:
  typedef Tr                        Tr_Base;
  typedef typename Tr_Base::Geom_traits        Geom_traits;
  typedef typename Geom_traits::Point_2        Point;
  typedef typename Tr_Base::Vertex_handle     Vertex_handle;
  typedef typename Tr_Base::Face_handle       Face_handle;
  typedef typename Tr_Base::Vertex_iterator   Vertex_iterator;
  typedef typename Tr_Base::Vertex           Vertex;
  typedef typename Tr_Base::Locate_type       Locate_type;

 private:
  // here is the stack of triangulations which form the hierarchy
  Tr_Base*   hierarchy[Triangulation_hierarchy_2__maxlevel];
  Random random; // random generator

public:
  Triangulation_hierarchy_2(const Geom_traits& traits = Geom_traits());
  Triangulation_hierarchy_2(const Triangulation_hierarchy_2& tr);

  Triangulation_hierarchy_2 &operator=(const  Triangulation_hierarchy_2& tr);
  ~Triangulation_hierarchy_2();

  //Helping
  void copy_triangulation(const Triangulation_hierarchy_2 &tr);
  void swap(Triangulation_hierarchy_2 &tr);
  void clear();

  // CHECKING
  bool is_valid() const;

  // INSERT REMOVE
  Vertex_handle insert(const Point &p);
  Vertex_handle push_back(const Point &p);
 
  template < class InputIterator >
  int insert(InputIterator first, InputIterator last)
    {
      int n = number_of_vertices();
      while(first != last){
	insert(*first);
	++first;
      }
      return number_of_vertices() - n;
    }

  void remove_degree_3(Vertex_handle  v);
  void remove_first(Vertex_handle  v);
  void remove_second(Vertex_handle v);
  void remove(Vertex_handle  v);

  //LOCATE
  Face_handle  locate(const Point& p, Locate_type& lt,int& li) const;
  Face_handle  locate(const Point& p) const;

private:
  void  locate(const Point& p,
	       Locate_type& lt,
	       int& li,
	       Face_handle pos[Triangulation_hierarchy_2__maxlevel]) const;
  int random_level();


 // added to make the test program of usual triangulations work
  // undocuumented
public:
  
  Vertex_handle insert(const Point  &p, Face_handle start){
    return Tr_Base::insert(p,start);
  }
  Vertex_handle insert(const Point& p,
		       Locate_type lt,
		       Face_handle loc, int li ){
    return Tr_Base::insert(p);
  }

  Face_handle  locate(const Point& p, 
		      Locate_type& lt,
		      int& li,
		      Face_handle start) const{
    return Tr_Base::locate(p, lt, li, start);
  }

};



template <class Tr >
Triangulation_hierarchy_2<Tr>::
Triangulation_hierarchy_2(const Geom_traits& traits)
  : Tr_Base(traits), random((long)0)
{ 
  hierarchy[0] = this; 
  for(int i=1;i<Triangulation_hierarchy_2__maxlevel;++i)
    hierarchy[i] = new Tr_Base(traits);
}


// copy constructor duplicates vertices and faces
template <class Tr>
Triangulation_hierarchy_2<Tr>::
Triangulation_hierarchy_2(const Triangulation_hierarchy_2<Tr> &tr)
    : Tr_Base(), random((long)0)
{ 
  // create an empty triangulation to be able to delete it !
  hierarchy[0] = this; 
  for(int i=1;i<Triangulation_hierarchy_2__maxlevel;++i)
    hierarchy[i] = new Tr_Base(tr.geom_traits());
  copy_triangulation(tr);
} 
 

//Assignement
template <class Tr>
Triangulation_hierarchy_2<Tr> &
Triangulation_hierarchy_2<Tr>::
operator=(const Triangulation_hierarchy_2<Tr> &tr)
{
  copy_triangulation(tr);
  return *this;
}


template <class Tr>
void
Triangulation_hierarchy_2<Tr>::   
copy_triangulation(const Triangulation_hierarchy_2<Tr> &tr)
{
  std::map< const void*, void*, std::less<const void*> > V;
  {
    for(int i=0;i<Triangulation_hierarchy_2__maxlevel;++i)
    hierarchy[i]->copy_triangulation(*tr.hierarchy[i]);
  }
  //up and down have been copied in straightforward way
  // compute a map at lower level
  {
    for( Vertex_iterator it=hierarchy[0]->vertices_begin(); 
	 it != hierarchy[0]->vertices_end(); ++it) {
      if (it->up()) V[ ((Vertex*)(it->up()))->down() ] = &(*it);
    }
  }
  {
    for(int i=1;i<Triangulation_hierarchy_2__maxlevel;++i) {
      for( Vertex_iterator it=hierarchy[i]->vertices_begin(); 
	   it != hierarchy[i]->vertices_end(); ++it) {
	// down pointer goes in original instead in copied triangulation
	it->set_down(V[it->down()]);
	// make reverse link
	((Vertex*)(it->down()))->set_up( &(*it) );
	// make map for next level
	if (it->up()) V[ ((Vertex*)(it->up()))->down() ] = &(*it);
      }
    }
  }
}

template <class Tr>
void
Triangulation_hierarchy_2<Tr>:: 
swap(Triangulation_hierarchy_2<Tr> &tr)
{
//   Tr_Base** h= hierarchy;
//   hierarchy = tr.hierarchy;
//   tr.hierarchy = h;
  Tr_Base* temp;
  Tr_Base::swap(tr);
  for(int i= 1; i<Triangulation_hierarchy_2__maxlevel; ++i){
    temp = hierarchy[i];
    hierarchy[i] = tr.hierarchy[i];
    tr.hierarchy[i]= temp;
  }
}

template <class Tr>
Triangulation_hierarchy_2<Tr>:: 
~Triangulation_hierarchy_2()
{
  clear();
  for(int i= 1; i<Triangulation_hierarchy_2__maxlevel; ++i){ 
    delete hierarchy[i];
  }
}

template <class Tr>
void
Triangulation_hierarchy_2<Tr>:: 
clear()
{
        for(int i=0;i<Triangulation_hierarchy_2__maxlevel;++i)
	hierarchy[i]->clear();
}


template <class Tr>
bool
Triangulation_hierarchy_2<Tr>:: 
is_valid() const
{
  bool result = true;
  int i;
  Vertex_iterator it;
  //verify correctness of triangulation at all levels
  for(i=0;i<Triangulation_hierarchy_2__maxlevel;++i)
	result = result && hierarchy[i]->is_valid();
  //verify that lower level has no down pointers
  for( it = hierarchy[0]->vertices_begin(); 
       it != hierarchy[0]->vertices_end(); ++it) 
    result = result && ( it->down() == 0 );
  //verify that other levels has down pointer and reciprocal link is fine
  for(i=1;i<Triangulation_hierarchy_2__maxlevel;++i)
    for( it = hierarchy[i]->vertices_begin(); 
	 it != hierarchy[i]->vertices_end(); ++it) 
      result = result && 
	       ( ((Vertex*)((Vertex*)it->down())->up()) ==  &(*it) );
  return result;
}

  
template <class Tr>
Triangulation_hierarchy_2<Tr>::Vertex_handle
Triangulation_hierarchy_2<Tr>::
insert(const Point &p)
{
  int vertex_level = random_level();
  //   debug purpose
  std::cout << "niveau " << vertex_level << std::endl << std::flush;
  Locate_type lt;
  int i;
  // locate using hierarchy
  Face_handle positions[Triangulation_hierarchy_2__maxlevel];
  locate(p,lt,i,positions);
  //insert at level 0
  Vertex_handle vertex=hierarchy[0]->insert(p,positions[0]);
  Vertex_handle previous=vertex;
  Vertex_handle first = vertex;
      
  int level  = 1;
  while (level <= vertex_level ){
    vertex=hierarchy[level]->insert(p,positions[level]);
    vertex->set_down((void *) &*previous);// link with level above
    previous->set_up((void *) &*vertex);
    previous=vertex;
    level++;
  }
  return first;
}

template <class Tr>
inline
Triangulation_hierarchy_2<Tr>::Vertex_handle
Triangulation_hierarchy_2<Tr>::
push_back(const Point &p)
{
  return insert(p);
}

template <class Tr>
void 
Triangulation_hierarchy_2<Tr>::
remove(Vertex_handle v )
{
  void * u=v->up();
  int l = 0 ;
  while(1){
    hierarchy[l++]->remove(v);
    if (!u) break; 
    if(l>Triangulation_hierarchy_2__maxlevel) break;
    v=(Vertex*)u; u=v->up();
  }
}

template <class Tr>
inline void 
Triangulation_hierarchy_2<Tr>::
remove_degree_3(Vertex_handle v )
{
  remove(v);
}

template <class Tr>
inline void 
Triangulation_hierarchy_2<Tr>::
remove_first(Vertex_handle v )
{
  remove(v);
}

template <class Tr>
inline void 
Triangulation_hierarchy_2<Tr>::
remove_second(Vertex_handle v )
{
  remove(v);
}

template <class Tr>
Triangulation_hierarchy_2<Tr>::Face_handle 
Triangulation_hierarchy_2<Tr>::
locate(const Point& p, Locate_type& lt, int& li) const
{
  Face_handle positions[Triangulation_hierarchy_2__maxlevel];
  locate(p,lt,li,positions);
  return positions[0];
}

template <class Tr>
Triangulation_hierarchy_2<Tr>::Face_handle 
Triangulation_hierarchy_2<Tr>::
locate(const Point& p) const
{
  Locate_type lt;
  int li;
  return locate(p, lt, li);
}

template <class Tr>
void
Triangulation_hierarchy_2<Tr>::
locate(const Point& p,
       Locate_type& lt,
       int& li,
       Face_handle pos[Triangulation_hierarchy_2__maxlevel]) const
{
  Face_handle position;
  Vertex_handle nearest;
  int level  = Triangulation_hierarchy_2__maxlevel;
  typename Geom_traits::Less_distance_to_point_2 
    closer = geom_traits().less_distance_to_point_2_object(p);

  // find the highest level with enough vertices
  while (hierarchy[--level]->number_of_vertices() 
	 < Triangulation_hierarchy_2__minsize){
    if ( ! level) break;  // do not go below 0
  }
  for (int i=level+1; i<Triangulation_hierarchy_2__maxlevel;++i) pos[i]=0;
  while(level > 0) {
    pos[level]=position=hierarchy[level]->locate(p,position);  
    // locate at that level from "position"
    // result is stored in "position" for the next level
    // find the nearest between vertices 0 and 1
    if (hierarchy[level]->is_infinite(position->vertex(0)))
      nearest = position->vertex(1);
    else if (hierarchy[level]->is_infinite(position->vertex(1)))
      nearest = position->vertex(0);
     else if ( closer(position->vertex(0)->point(),
		      position->vertex(1)->point()))
      nearest = position->vertex(0);
    else
      nearest = position->vertex(1);
    // compare to vertex 2
    if ( !  hierarchy[level]->is_infinite(position->vertex(2)))
      if ( closer( position->vertex(2)->point(),
		   nearest->point()))
	nearest = position->vertex(2);
    // go at the same vertex on level below
    nearest = (Vertex*)( nearest->down() );
    position = nearest->face();                // incident face
    --level;
  }
  pos[0]=hierarchy[level]->locate(p,lt,li,position);  // at level 0
}


template <class Tr>
int
Triangulation_hierarchy_2<Tr>::
random_level()
{
  int l = 0;
  while (1) {
    if ( random(Triangulation_hierarchy_2__ratio) ) break;
    ++l;
  }
  if (l >= Triangulation_hierarchy_2__maxlevel)
    l = Triangulation_hierarchy_2__maxlevel -1;
  return l;
}

CGAL_END_NAMESPACE
#endif //TRIANGULATION_HIERARCHY_2_H