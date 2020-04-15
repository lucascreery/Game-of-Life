#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include <stdio.h>

//sf::Time frameTime;
int width = 100;
int height = 100;
int cells[100][100];
int newCells[100][100];
bool gameActive = false;

int main() {
  sf::RenderWindow window(sf::VideoMode(1000, 1000), "Conway's Game of Life");
  float XScaleFactor = 1000 / 100;
  float YScaleFactor = 1000 / 100;
  srand(time(0));

  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      cells[i][j] = rand() % 2;
    }
  }

  //sf::Clock clock;

  window.clear(sf::Color::White);

  while (window.isOpen()) {
      sf::Event event;
      while (window.pollEvent(event)) {
        switch(event.type){
          case sf::Event::MouseButtonPressed:
            if(event.mouseButton.x < 60 && event.mouseButton.y < 60){
              if(gameActive){
                gameActive = false;
              }else{
                gameActive = true;
              }
            }else if(event.mouseButton.x > 60 && event.mouseButton.y < 60 && event.mouseButton.x < 120){
              for(int i = 0; i < width; i++){
                for(int j = 0; j < height; j++){
                  cells[i][j] = 0;
                }
              }
            }else if(event.mouseButton.x > 120 && event.mouseButton.y < 60 && event.mouseButton.x < 180){
              for(int i = 0; i < width; i++){
                for(int j = 0; j < height; j++){
                  cells[i][j] = rand() % 2;
                }
              }
            }else{
              if(!gameActive){
                int cellClicked[2] = {(int)(event.mouseButton.x / 10), (int)(event.mouseButton.y / 10)};
                cells[cellClicked[0]][cellClicked[1]] = 1 - cells[cellClicked[0]][cellClicked[1]];
              }
            }
          break;

          case sf::Event::Closed:
          window.close();
          break;

        }
      }

      if(gameActive){

        for(int i = 0; i < width; i++){
          for(int j = 0; j < height; j++){
            newCells[i][j] = cells[i][j];
          }
        }

        for(int i = 0; i < width; i++){
          for(int j = 0; j < height; j++){
            int left = (i - 1 + width) % width;
            int right = (i + 1 + width) % width;
            int above = (j - 1 + height) % height;
            int below = (j + 1 + height) % height;
            int points = cells[left][above] + cells[i][above] + cells[right][above] + cells[left][j] + cells[right][j] + cells[left][below] + cells[i][below] + cells[right][below];
            switch(cells[i][j]){
              case 1:
              if(points < 2){
                newCells[i][j] = 0;
              }
              if(points > 3){
                newCells[i][j] = 0;
              }
              break;

              case 0:
              if(points == 3){
                newCells[i][j] = 1;
              }
              break;
            }
          }
        }

        for(int i = 0; i < width; i++){
          for(int j = 0; j < height; j++){
            cells[i][j] = newCells[i][j];
          }
        }

      }

      for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
          sf::RectangleShape cell(sf::Vector2f(XScaleFactor, YScaleFactor));
          cell.setFillColor(sf::Color(250 - cells[i][j] * 250, 250 - cells[i][j] * 250, 250 - cells[i][j] * 250));
          cell.setPosition(i*XScaleFactor, j*YScaleFactor);
          cell.setOutlineThickness(1.f);
          cell.setOutlineColor(sf::Color(100, 100, 100));
          window.draw(cell);
        }
      }

      sf::Texture playPauseTex;
      if(gameActive){
        playPauseTex.loadFromFile("toggleicon.png", sf::IntRect(300,90, 190, 350));
      }else{
        playPauseTex.loadFromFile("toggleicon.png", sf::IntRect(30, 100, 273, 316));
      }
      sf::RectangleShape playPauseButton(sf::Vector2f(60.f, 60.f));
      playPauseButton.setPosition(0, 0);
      playPauseButton.setTexture(&playPauseTex);
      window.draw(playPauseButton);

      sf::Texture resetTex;
      resetTex.loadFromFile("xicon.png");
      sf::RectangleShape resetButton(sf::Vector2f(60.f, 60.f));
      resetButton.setPosition(60, 0);
      resetButton.setTexture(&resetTex);
      window.draw(resetButton);

      sf::Texture refreshTex;
      refreshTex.loadFromFile("refreshicon.png");
      sf::RectangleShape refreshButton(sf::Vector2f(60.f, 60.f));
      refreshButton.setPosition(120, 0);
      refreshButton.setTexture(&refreshTex);
      window.draw(refreshButton);

      window.display();
  }

  return 0;
}
