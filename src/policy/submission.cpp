#include <cstdlib>

#include "../state/state.hpp"
#include "./submission.hpp"

int Submission::submission(State * state, int depth, int maximizing, int a, int b, int player){
  int value, result;
  if(!state->legal_actions.size())
        state->get_legal_actions();
  if(depth == 0 || !state->legal_actions.size()){
    result = state -> evaluate(player);
    return result;
  }
  if(maximizing){
    result = -2100000000;
    for(auto it : state -> legal_actions){
      State * next = state -> next_state(it);
      value = submission(next, depth - 1, 0, a, b, player);
      result = result > value ? result : value;
      a = a > result ? a : result;
      if(a >= b){
        break;
      }
    }
    return result;
  }else{
    result = 2100000000;
    for(auto it : state -> legal_actions){
      State * next = state -> next_state(it);
      //next->get_legal_actions();
      value = submission(next, depth - 1, 1, a, b, player);
      result = result < value ? result : value;
      b = b < result ? b : result;
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
Move Submission::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  auto actions = state->legal_actions;
  if(actions.size()){
    Move best;
    if(actions.size() >= 7){
      best = actions[6];
    }else{
      best = actions[0];
    }
    int nowvalue =-2147483647;
    for(auto it : actions){
      int temp = submission(state->next_state(it), depth - 1, 0, -10000, 10000, state->player);
      if(temp > nowvalue){
        nowvalue = temp;
        best = it;
      }
    }
    return best;
  }
}

