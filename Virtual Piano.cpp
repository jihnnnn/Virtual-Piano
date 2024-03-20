#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <unistd.h>
#include <string>
#include <iostream>

using namespace std;
using namespace sf;

class Piano{
private:
	RenderWindow window;
	vector<RectangleShape> outline;
	vector<RectangleShape> sharpKeys;
	
	Sound keyNote;
	SoundBuffer keyNoteBuffer;
	
	Clock clock;
	float time_interval;
	
	float majorPos, minorPos;
	bool isPressed, clockPause;
	
	void whiteKeys(){
		RectangleShape normalKey;
		normalKey.setSize(Vector2f(1900, 500));
		normalKey.setFillColor(Color::White);
		normalKey.setPosition(0,350);
		
		window.draw(normalKey);
	}
	
	void blackKeys(float posCounter, int counter, int i){
		int spacing = 170;
		float posX = 125;
		posX *= posCounter;
				
		for(i; i < counter; i++){
			sharpKeys.push_back(RectangleShape()); 
			sharpKeys.back().setSize(Vector2f(70, 450));
			sharpKeys.back().setFillColor(Color::Black);
			sharpKeys.back().setPosition(posX + i * spacing, 200);
			
			window.draw(sharpKeys[i]);
		}
	}
	
	void grayWhiteKeys(int posX){
        RectangleShape whiteKeyPressed;
        whiteKeyPressed.setSize(Vector2f(160, 500));
        whiteKeyPressed.setFillColor(Color(211, 211, 211));
        whiteKeyPressed.setPosition(posX,350);
        window.draw(whiteKeyPressed);
    }
    
    void grayBlackKeys(int posX){
        RectangleShape blackKeyPressed;
        blackKeyPressed.setSize(Vector2f(70, 300));
        blackKeyPressed.setFillColor(Color(128, 128, 128));
        blackKeyPressed.setPosition(posX,350);
        window.draw(blackKeyPressed);
    }
    	
	void grayPressed(bool isPressing, float whitePosX, float blackPosX) {
        if (isPressing == true) {
            if (whitePosX != 0) { 
                grayWhiteKeys(whitePosX);
                pianoDisplay();
            }
			 else { 
                grayBlackKeys(blackPosX);
                letters();
            }
        }
    }
	
	void keyOutline(){
		int spacing = 170;
		int posX = 160;
		
		for(int i = 0; i < 11; i++){
			outline.push_back(RectangleShape());
			outline.back().setSize(Vector2f(12, 500));
			outline.back().setFillColor(Color::Black);
			outline.back().setPosition(posX + i * spacing, 350);
			
			window.draw(outline[i]);
		}
	}
	
	bool loadSound(string filename){
		keyNoteBuffer.loadFromFile(filename);
		keyNote.setBuffer(keyNoteBuffer);
		keyNote.play();
	}
	
	void pianoDisplay(){
		keyOutline();
		blackKeys(1, 2, 0);
		blackKeys(2.5, 5, 2);
		blackKeys(5.15, 6, 4);
		blackKeys(7.85, 8, 5);
		letters();
	}
	void letters(){
		Letters(65, 750, 0, 70, "A" );
		Letters(235, 750, 0, 70, "S" );
		Letters(405, 750, 0, 70, "D" );
		Letters(575, 750, 0, 70, "F" );
		Letters(745, 750, 0, 70, "G" );
		Letters(915, 750, 0, 70, "H" );
		Letters(1085, 750, 0, 70, "J" );
		Letters(1255, 750, 0, 70, "K" );
		Letters(1425, 750, 0, 70, "L" );
		Letters(1600, 750, 0, 70, ";" );
		Letters(1770, 750, 0, 70, "'" );
		
		Letters(145, 575, 255, 45, "W" );
		Letters(320, 575, 255, 45, "E" );
		Letters(670, 575, 255, 45, "T" );
		Letters(845, 575, 255, 45, "Y" );
		Letters(1020, 575, 255, 45, "U" );
		Letters(1345, 575, 255, 45, "O" );
		Letters(1520, 575, 255, 45, "P" );
		Letters(1870, 575, 255, 45, "]" );
	}
	
	void Letters(int x, int y, int c, int size, string texts ){
		Font font;
		if(!font.loadFromFile("arial.ttf")){
			//handle error
		}
		Text text;
		text.setFont(font);
		text.setString(texts);
		text.setColor(Color(c, c, c));
		text.setCharacterSize (size);
		text.setPosition(x, y);
		window.draw(text);
	}
	
	void Title(int x, int y, int size, string titleName ){
		Font font;
		if(!font.loadFromFile("Lato-Thin.ttf")){
			//handle error
		}
		Text title;
		title.setFont(font);
		title.setString(titleName);
		title.setColor(Color::White);
		title.setCharacterSize (size);
		title.setPosition(x, y);
		window.draw(title);
		
		RectangleShape titleLine;
        titleLine.setSize(Vector2f(800, 5));
        titleLine.setFillColor(Color::White);
        titleLine.setPosition(550, 280);
        window.draw(titleLine);
	}

public:
	Piano() : window(VideoMode(1900, 950), "Virtual Piano"){
		isPressed = false;
		window.setKeyRepeatEnabled(false);	
			
		while(window.isOpen()){
			time_interval = clock.getElapsedTime().asSeconds();
			Event event;
			while(window.pollEvent(event)){
				if(event.type == Event::Closed){
					window.close();
				}	
				else if(event.type == Event::KeyPressed){			
					majorPos = whenWhitePressed(event.key.code);
					minorPos = whenBlackPressed(event.key.code);	
					isPressed = true;
				}
				else if(event.type == Event::KeyReleased){
					isPressed = false;
				}
			}
			
			
			whiteKeys();
			pianoDisplay();
			grayPressed(isPressed, majorPos, minorPos);
			Title(400, 100, 150, "Kumikinang Piano");
			
			window.display();
		}
	}
	
	float whenWhitePressed(Keyboard::Key key){
		float posX = 0;
		switch(key){
			case Keyboard::A:
				loadSound("C4.wav");
				posX = 0.1;
				break;
			case Keyboard::S:
				loadSound("D4.wav");
				posX = 170;
				break;
			case Keyboard::D:
				loadSound("E4.wav");
				posX = 340;
				break;
			case Keyboard::F:
				loadSound("F4.wav");
				posX = 510;
				break;
			case Keyboard::G:
				loadSound("G4.wav");
				posX = 680;
				break;
			case Keyboard::H:
				loadSound("A4.wav");
				posX = 850;
				break;
			case Keyboard::J:
				loadSound("B4.wav");
				posX = 1020;
				break;
			case Keyboard::K:
				loadSound("C5.wav");
				posX = 1190;
				break;
			case Keyboard::L:
				loadSound("D5.wav");
				posX = 1360;
				break;
			case Keyboard::SemiColon:
				loadSound("E5.wav");
				posX = 1530;
				break;
			case Keyboard::Quote:
				loadSound("F5.wav");
				posX = 1700;
				break;
			default:
				break;
		}
    	return posX;
	}

	float whenBlackPressed(Keyboard::Key key) {
	    float posX = 0;
	    switch (key) {
	        case Keyboard::W:
	            loadSound("C4sharp.wav");
	            posX = 125;
	            break;
	        case Keyboard::E:
	            loadSound("D4sharp.wav");
	            posX = 295; 
	            break;
	        case Keyboard::T:
	            loadSound("F4sharp.wav");
	            posX = 652; 
	            break;
	        case Keyboard::Y:
	            loadSound("G4sharp.wav");
	            posX = 822; 
	            break;
	        case Keyboard::U:
	            loadSound("A4sharp.wav");
	            posX = 992; 
	            break;
	        case Keyboard::O:
	            loadSound("C5sharp.wav");
	            posX = 1324; 
	            break;
	        case Keyboard::P:
	            loadSound("D5sharp.wav");
	            posX = 1494; 
	            break;
	        case Keyboard::RBracket:
	            loadSound("F5sharp.wav");
	            posX =  1831; 
	            break;
	        default:
	        	posX = -300;
	            break;
	    }
	    return posX;
	}
};

int main(){
	Piano piano;
	return 0;
}

