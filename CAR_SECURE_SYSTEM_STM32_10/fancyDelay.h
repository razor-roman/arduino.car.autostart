class FancyDelay{
  unsigned long _period, _next;
  public:
  FancyDelay(unsigned long period) : _period(period) {
    _next = millis() + _period;
  }
  bool ready(){
    if(millis() >= _next){
      _next += _period;
      return true;
    }
    return false;
  }
};
