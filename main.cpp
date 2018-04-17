#include "SFML/Graphics.hpp"
#include <iostream>
#include <cmath>
void set_Paddles(sf::RectangleShape& paddle1, sf::RectangleShape& paddle2);

int main(void)
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Pong");
	sf::Font arial;
	sf::Text player1, player2, score1, score2;
	sf::RectangleShape paddle1, paddle2;
	sf::CircleShape ball;
	float alternate = -5;
	float intersection, normInter, realBounceAngle, collisionCO, xCO = -5, yCO = 0;
	float playerMovespeed = 6, ballMovespeed = 9;
	window.setFramerateLimit(60);
	float bounceAngle = (5 * 3.14159) / 12;


	if (!arial.loadFromFile("images/arial.ttf"));

	/* PADDLE AND BALL */
	/////////////////////////////////////////////////////////////////
	set_Paddles(paddle1, paddle2);
	paddle1.getFillColor();
	ball.setFillColor(sf::Color::White);
	ball.setRadius(7);
	ball.setPosition(320, 240);
	/////////////////////////////////////////////////////////////////


	/* PLAYER TEXT ABOVE */
	/////////////////////////////////////////////////////////////////
	player1.setFont(arial);
	player1.setColor(sf::Color::White);
	player1.setCharacterSize(24);
	player1.setStyle(sf::Text::Bold);
	player1.setString("Player 1");
	player1.move(5, 0);
	player2.setFont(arial);
	player2.setColor(sf::Color::White);
	player2.setCharacterSize(24);
	player2.setStyle(sf::Text::Bold);
	player2.setString("Player 2");
	player2.move(535, 0);
	/////////////////////////////////////////////////////////////////

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}
		/* RESET SWITCH */
		/////////////////////////////////////////////////////
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			ball.setPosition(320, 240);
			alternate = -alternate;
			xCO = alternate;
			yCO = 0;
		}
		/////////////////////////////////////////////////////
		
		/* KeyBoard movement for 2 players */
		/////////////////////////////////////////////////////
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !(paddle2.getPosition().y < 35))
			paddle2.move(0, -playerMovespeed);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !(paddle1.getPosition().y < 35))
			paddle1.move(0, -playerMovespeed);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !(paddle2.getPosition().y > 405))
			paddle2.move(0, playerMovespeed);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !(paddle1.getPosition().y > 405))
			paddle1.move(0, playerMovespeed);
		/////////////////////////////////////////////////////

		/* Ball movement */
		/////////////////////////////////////////////////////
		if (ball.getPosition().x <= 0 || ball.getPosition().x >= 640)
		{
			ball.setPosition(320, 240);
			alternate = -alternate;
			xCO = alternate;
			yCO = 0;
		}

		if (paddle1.getGlobalBounds().intersects(ball.getGlobalBounds()))
		{
			intersection = (paddle1.getPosition().y + (75 / 2)) - ball.getPosition().y;
			normInter = (intersection / (75 / 2));
			realBounceAngle = normInter * bounceAngle;
			xCO = ballMovespeed * cos(realBounceAngle);
			if (xCO < 0)
				xCO = -xCO;
			yCO = ballMovespeed * -sin(realBounceAngle);
		}

		if (paddle2.getGlobalBounds().intersects(ball.getGlobalBounds()))
		{
			intersection = (paddle2.getPosition().y + (75 / 2)) - ball.getPosition().y;
			normInter = (intersection / (75 / 2));
			realBounceAngle = normInter * bounceAngle;
			xCO = ballMovespeed * -cos(realBounceAngle);
			if (xCO > 0)
				xCO = -xCO;
			yCO = ballMovespeed * -sin(realBounceAngle);
		}

		if (ball.getPosition().y >= 470 || ball.getPosition().y <= 24)
			yCO = -yCO;
		
		ball.move(xCO, yCO);
		/////////////////////////////////////////////////////

		window.clear(sf::Color::Black);
		window.draw(ball);
		window.draw(paddle1);
		window.draw(paddle2);
		window.draw(player1);
		window.draw(player2);
		window.display();
	}
}

//function to draw everything
void set_Paddles(sf::RectangleShape& paddle1, sf::RectangleShape& paddle2)
{

	paddle1.setFillColor(sf::Color::White);
	paddle1.setSize(sf::Vector2f(10, 75));
	paddle1.setPosition(0, 210);
	paddle2.setFillColor(sf::Color::White);
	paddle2.setSize(sf::Vector2f(10, 75));
	paddle2.setPosition(630, 210);
}