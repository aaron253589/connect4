#ifndef AUTO_PLAYER
#define AUTO_PLAYER

    #include "PlayerImpl.cpp"
  #include "Game.hpp"

class AutoPlayer : public PlayerImpl{
    private:
      uint8_t getProximity(const uint64_t a, const uint64_t b);
      long getPlayerScore(const uint64_t currentPlayerBoard, const uint64_t oppositionPlayerBoard);
      long getOverallScore(const uint64_t currentPlayerBoard, const uint64_t oppositionPlayerBoard);
      long playNextMove(uint64_t playerA, uint64_t playerB, int depth, bool playerIndicator);
      int getNextMove(uint64_t currentPlayerState, uint64_t oppositionPlayerState, const std::vector<uint64_t>& winningPositions);
    
    public:
        bool nextMove();
        AutoPlayer(std::string* playerName, Game& game);
        };
#endif