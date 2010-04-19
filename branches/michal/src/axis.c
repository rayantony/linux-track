#include <assert.h>
#include "axis.h"
#include "spline.h"
#include "utils.h"

struct axis_def{
  splines_def *curve_defs;
  splines *curves;
  bool valid;
  float l_factor, r_factor;
  float limits; //Input value limits - normalize into <-1;1>
};

float val_on_axis(struct axis_def *axis, float x)
{
  assert(axis != NULL);
  assert(axis->curve_defs != NULL);
  assert(axis->curves != NULL);
  
  if(!(axis->valid)){
    curve2pts(axis->curve_defs, axis->curves);
  }
  x = x / axis->limits;
  if(x < -1.0){
    x = -1.0;
  }
  if(x > 1.0){
    x = 1.0;
  }
  float y = spline_point(axis->curves, x);
  if(x < 0.0){
    return y * axis->l_factor; 
  }else{
    return y * axis->r_factor; 
  }
}

bool is_symetrical(const struct axis_def *axis)
{
  assert(axis != NULL);
  assert(axis->curve_defs != NULL);
  assert(axis->curves != NULL);
  
  if((axis->l_factor == axis->r_factor) && 
     (axis->curve_defs->l_curvature == axis->curve_defs->l_curvature)){
    return true;
  }else{
    return false;
  }
}

bool set_deadzone(struct axis_def *axis, float dz)
{
  assert(axis != NULL);
  assert(axis->curve_defs != NULL);
  assert(axis->curves != NULL);
  
  axis->valid = false;
  axis->curve_defs->dead_zone = dz;
  
  return true;
}

float get_deadzone(struct axis_def *axis)
{
  assert(axis != NULL);
  assert(axis->curve_defs != NULL);
  assert(axis->curves != NULL);
  
  return axis->curve_defs->dead_zone;
}

bool set_lcurv(struct axis_def *axis, float c)
{
  assert(axis != NULL);
  assert(axis->curve_defs != NULL);
  assert(axis->curves != NULL);
  
  axis->valid = false;
  axis->curve_defs->l_curvature = c;
  
  return true;
}

float get_lcurv(struct axis_def *axis)
{
  assert(axis != NULL);
  assert(axis->curve_defs != NULL);
  assert(axis->curves != NULL);
  
  return axis->curve_defs->l_curvature;
}

bool set_rcurv(struct axis_def *axis, float c)
{
  assert(axis != NULL);
  assert(axis->curve_defs != NULL);
  assert(axis->curves != NULL);
  
  axis->valid = false;
  axis->curve_defs->r_curvature = c;
  
  return true;
}

float get_rcurv(struct axis_def *axis)
{
  assert(axis != NULL);
  assert(axis->curve_defs != NULL);
  assert(axis->curves != NULL);
  
  return axis->curve_defs->r_curvature;
}

bool set_lmult(struct axis_def *axis, float m1)
{
  assert(axis != NULL);
  assert(axis->curve_defs != NULL);
  assert(axis->curves != NULL);
  
  axis->valid = false;
  axis->l_factor = m1;
  
  return true;
}

float get_lmult(struct axis_def *axis)
{
  assert(axis != NULL);
  assert(axis->curve_defs != NULL);
  assert(axis->curves != NULL);
  
  return axis->l_factor;
}

bool set_rmult(struct axis_def *axis, float m1)
{
  assert(axis != NULL);
  assert(axis->curve_defs != NULL);
  assert(axis->curves != NULL);
  
  axis->valid = false;
  axis->r_factor = m1;
  
  return true;
}

float get_rmult(struct axis_def *axis)
{
  assert(axis != NULL);
  assert(axis->curve_defs != NULL);
  assert(axis->curves != NULL);
  
  return axis->r_factor;
}

bool set_limits(struct axis_def *axis, float lim)
{
  assert(axis != NULL);
  assert(axis->curve_defs != NULL);
  assert(axis->curves != NULL);
  
  axis->valid = false;
  axis->limits = lim;
  
  return true;
}

float get_limits(struct axis_def *axis)
{
  assert(axis != NULL);
  assert(axis->curve_defs != NULL);
  assert(axis->curves != NULL);
  
  return axis->limits;
}

void init_axis(struct axis_def **axis)
{
  assert(axis != NULL);
  (*axis) = (struct axis_def *)my_malloc(sizeof(struct axis_def));
  (*axis)->curve_defs = (splines_def *)my_malloc(sizeof(splines_def));
  (*axis)->curves = (splines *)my_malloc(sizeof(splines));
}

void close_axis(struct axis_def **axis)
{
  assert(axis != NULL);
  assert((*axis) != NULL);
  assert((*axis)->curve_defs != NULL);
  assert((*axis)->curves != NULL);
  
  free((*axis)->curve_defs);
  (*axis)->curve_defs = NULL;
  free((*axis)->curves);
  (*axis)->curves = NULL;
  free(*axis);
  (*axis) = NULL;
}