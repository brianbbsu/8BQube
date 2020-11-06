pdd center;//sort base
int Quadrant(pdd a) {
  if(a.X > 0 && a.Y >= 0) return 1;
  if(a.X <= 0 && a.Y > 0) return 2;
  if(a.X < 0 && a.Y <= 0) return 3;
  if(a.X >= 0 && a.Y < 0) return 4;
}
bool cmp(pll a, pll b) {
  a = a - center, b = b - center;
  if (Quadrant(a) != Quadrant(b))
    return Quadrant(a) < Quadrant(b);
  if (cross(b, a) == 0) return abs2(a) < abs2(b);
  return cross(a, b) > 0;
}
bool cmp(pdd a, pdd b) {
  a = a - center, b = b - center;
  if(fabs(atan2(a.Y, a.X) - atan2(b.Y, b.X)) > eps)
    return atan2(a.Y, a.X) < atan2(b.Y, b.X);
  return abs(a) < abs(b);
}
