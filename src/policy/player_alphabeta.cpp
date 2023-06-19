#include <cstdlib>

#include "../state/state.hpp"
#include "./player_alphabeta.hpp"

int Alphabeta::alphabeta(State * state, int depth, int maximizing, int a, int b){
  int value, result;
  if(depth == 0 || !state->legal_actions.size()){
    result = state -> evaluate();
    return result;
  }
  if(maximizing){
    result = -2147483647;
    for(auto it : state -> legal_actions){
      State * next = state -> next_state(it);
      //next->get_legal_actions();
      value = alphabeta(next, depth - 1, 0, a, b);
      result = result > value ? result : value;
      a = result > a ? result : a;
      if(a >= b){
        break;
      }
    }
    return result;
  }else{
    result = 2147483647;
    for(auto it : state -> legal_actions){
      State * next = state -> next_state(it);
      //next->get_legal_actions();
      value = alphabeta(next, depth - 1, 1, a, b);
      result = result < value ? result : value;
      b = result < b ? result : b;
      if(b <= a){
        break;
      }
    }
    return result;
  }
}
/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Alphabeta::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  auto actions = state->legal_actions;
  Move best = actions[0];
  int nowvalue =-2147483647;
  for(auto it : actions){
    int temp = alphabeta(state->next_state(it), depth - 1, 1, 0, 0);//a?b?
    if(temp > nowvalue){
      nowvalue = temp;
      best = it;
    }
  }
  return best;
}

