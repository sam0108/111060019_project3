#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax.hpp"

int Minimax::minimax(State * state, int depth, int maximizing, int player){
  int value, result = 0;
  if(!state->legal_actions.size())
    state->get_legal_actions();
  if(depth == 0 || !state->legal_actions.size()){
    result = state -> evaluate(player);
    return result;
  }
  if(maximizing){
    result = -2147483647;
    for(auto it : state -> legal_actions){
      State * next = state -> next_state(it);
      //next->get_legal_actions();
      value = minimax(next, depth - 1, 0, player);
      result = result > value ? result : value;
    }
    return result;
  }else{
    result = 2147483647;
    for(auto it : state -> legal_actions){
      State * next = state -> next_state(it);
      //next->get_legal_actions();
      value = minimax(next, depth - 1, 1, player);
      result = result < value ? result : value;
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
Move Minimax::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  auto actions = state->legal_actions;
  Move best = actions[0];
  int nowvalue =-2147483647;
  for(auto it : actions){
    int temp = minimax(state->next_state(it), depth - 1, 0, state->player);
    if(temp > nowvalue){
      nowvalue = temp;
      best = it;
    }
  }
  return best;
}

