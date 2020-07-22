#include "Game.h"

void Game::Input_Globe() {
	cout << "so>?" << endl;
}

Vector2i Game::Input() {
	//Event event_global;
	while (window.pollEvent(event_global)) {
		// globe quit for console game
		if (event_global.type == Event::Closed) {
			gamequit = true;
			window.close();
		}
		
		// background music sound controller
		if (event_global.type == sf::Event::EventType::KeyReleased && event_global.key.code == sf::Keyboard::PageUp)
		{
			if (sound_volume < 95)		sound_volume += 5;
			music_bg.setVolume(sound_volume);
		}
		else if (event_global.type == sf::Event::EventType::KeyReleased && event_global.key.code == sf::Keyboard::PageDown)
		{
			if (sound_volume > 5)		sound_volume -= 5;
			music_bg.setVolume(sound_volume);
		}

		// when game begin yet is showing the main menu
		if (gamestart) {
			// change style
			if (event_global.type == sf::Event::EventType::KeyReleased && event_global.key.code == sf::Keyboard::A) {
				change_bg = true;
				if (globe_style_mode == 0) globe_style_mode = 1;
				else if (globe_style_mode == 1) globe_style_mode = 0;
			}
			if (event_global.type == Event::MouseButtonPressed && event_global.mouseButton.button == Mouse::Left) {
				//Mouse::getPosition(window) = Mouse::getPosition(window);
				if (Mouse::getPosition(window).x > 570 && Mouse::getPosition(window).x < (570 + 80) && Mouse::getPosition(window).y > 50 && Mouse::getPosition(window).y < (50 + 400)){ 
					gamestart_go.enable_down_button();
				}
				else if (Mouse::getPosition(window).x > 470 && Mouse::getPosition(window).x < (470+ 80) && Mouse::getPosition(window).y > 90 && Mouse::getPosition(window).y < (90 + 400)){
					gamestart_info.enable_down_button();
				}
				else if (Mouse::getPosition(window).x > 370 && Mouse::getPosition(window).x < (370 + 80) && Mouse::getPosition(window).y > 130 && Mouse::getPosition(window).y < (130 + 400))	{
					gamestart_quit.enable_down_button();
				}
			}
			if (event_global.type == Event::MouseButtonReleased && event_global.mouseButton.button == Mouse::Left) {
				Mouse::getPosition(window) = Mouse::getPosition(window);
				if (Mouse::getPosition(window).x > 570 && Mouse::getPosition(window).x < (570 + 80) && Mouse::getPosition(window).y > 50 && Mouse::getPosition(window).y < (50 + 400)) {
					gamestart_go.enable_diabled_button();
				}
				else if (Mouse::getPosition(window).x > 470 && Mouse::getPosition(window).x < (470 + 80) && Mouse::getPosition(window).y > 90 && Mouse::getPosition(window).y < (90 + 400)) {
					gamestart_info.enable_diabled_button();
				}
				else if (Mouse::getPosition(window).x > 370 && Mouse::getPosition(window).x < (370 + 80) && Mouse::getPosition(window).y > 130 && Mouse::getPosition(window).y < (130 + 400)) {
					gamestart_quit.enable_diabled_button();
				}
			}
			if (!gamestart_go.is_down && !gamestart_info.is_down && !gamestart_quit.is_down) {
				if (event_global.type == sf::Event::MouseMoved)
				{
					// control button of cancel in hover state
					if (event_global.mouseMove.x > 570 && event_global.mouseMove.x < (570 + 80) && event_global.mouseMove.y > 50 && event_global.mouseMove.y < (50 + 400))
					{
						if (gamestart_go.is_normal) button_animate_count = 0;
						gamestart_go.enable_hover_button();
					}
					else {
						gamestart_go.enable_normal_button();
					}
					// control button of assure
					if (event_global.mouseMove.x > 470 && event_global.mouseMove.x < (470 + 80) && event_global.mouseMove.y > 90 && event_global.mouseMove.y < (90 + 400))
					{
						if (gamestart_info.is_normal) button_animate_count = 0;
						gamestart_info.enable_hover_button();
					}
					else {
						gamestart_info.enable_normal_button();
					}
					// control button of discard in hover state
					if (event_global.mouseMove.x > 370 && event_global.mouseMove.x < (370 + 80) && event_global.mouseMove.y > 130 && event_global.mouseMove.y < (130 + 400))
					{
						if (gamestart_quit.is_normal) button_animate_count = 0;
						gamestart_quit.enable_hover_button();
					}
					else {
						gamestart_quit.enable_normal_button();
					}
				}
			}

		}


		// when begin to choose start game , choose game mode for double player or more  -----------single-player or muti-player
		if (net_chosen) {
			// change style
			if (event_global.type == sf::Event::EventType::KeyReleased && event_global.key.code == sf::Keyboard::A) {
				change_bg = true;
				if (globe_style_mode == 0) globe_style_mode = 1;
				else if (globe_style_mode == 1) globe_style_mode = 0;
			}
			if (event_global.type == sf::Event::MouseMoved) {
				if (!button_gamechoose.is_down) {
					// control button of return-menu in hover state
					if (event_global.mouseMove.x > 430 &&
						event_global.mouseMove.x < (430 + 135) &&
						event_global.mouseMove.y > 174 &&
						event_global.mouseMove.y < (174 + 53)) {
						button_gamechoose.enable_hover_button();
						button_gamechoose.sprite_hover.setPosition(383, 188);
					}
					else if (event_global.mouseMove.x > 430 &&
						event_global.mouseMove.x < (430 + 135) &&
						event_global.mouseMove.y > 250 &&
						event_global.mouseMove.y < (250 + 53)) {
						button_gamechoose.enable_hover_button();
						button_gamechoose.sprite_hover.setPosition(383, 266);
					}
					else {
						button_gamechoose.enable_normal_button();
					}
				}
				// control button of return-menu in hover state
				if (return_button.is_normal || return_button.is_hover) {
					if (event_global.mouseMove.x > 890 && event_global.mouseMove.x < (890 + 100) && event_global.mouseMove.y > 640 && event_global.mouseMove.y < (640 + 90)) {
						return_button.enable_hover_button();
					}
					else {
						return_button.enable_normal_button();
					}
				}
			}

			if (event_global.type == Event::MouseButtonPressed && event_global.mouseButton.button == Mouse::Left) {
				//mouse_count_clock_two = Mouse::getPosition(window);
				if (Mouse::getPosition(window).x > 890 &&
					Mouse::getPosition(window).x < (890 + 100) &&
					Mouse::getPosition(window).y > 640 &&
					Mouse::getPosition(window).y < (640 + 90)) {
					return_button.enable_down_button();
				}
				else if (Mouse::getPosition(window).x > 430 &&
					Mouse::getPosition(window).x < (430 + 135) &&
					Mouse::getPosition(window).y > 174 &&
					Mouse::getPosition(window).y < (174 + 53)) {
					button_gamechoose.enable_down_button();
					game_model = single_player;
					
				}
				else if (Mouse::getPosition(window).x > 430 &&
					Mouse::getPosition(window).x < (430 + 135) &&
					Mouse::getPosition(window).y > 250 &&
					Mouse::getPosition(window).y < (250 + 53)) {
					button_gamechoose.enable_down_button();
					game_model = muti_player;
					//send_packet()
				}
			}
			if (event_global.type == Event::MouseButtonReleased && event_global.mouseButton.button == Mouse::Left) {
				//mouse_count_clock_two = Mouse::getPosition(window);
				if (Mouse::getPosition(window).x > 890 && Mouse::getPosition(window).x < (890 + 100) && Mouse::getPosition(window).y > 640 && Mouse::getPosition(window).y < (640 + 90)) {
					return_button.enable_diabled_button();
				}
			}

		}
		// when begin to choose start game , choose game mode for double player or more
		if (gamechoose) {
			// change style
			if (event_global.type == sf::Event::EventType::KeyReleased && event_global.key.code == sf::Keyboard::A) {
				change_bg = true;
				if (globe_style_mode == 0) globe_style_mode = 1;
				else if (globe_style_mode == 1) globe_style_mode = 0;
			}
			if (event_global.type == sf::Event::MouseMoved) {
				if (!button_gamechoose.is_down) {

					// control button of return-menu in hover state
					if (event_global.mouseMove.x > 430 &&
						event_global.mouseMove.x < (430 + 135) &&
						event_global.mouseMove.y > 174 &&
						event_global.mouseMove.y < (174 + 53)) {
						button_gamechoose.enable_hover_button();
						button_gamechoose.sprite_hover.setPosition(383, 188);
					}
					else if (event_global.mouseMove.x > 430 &&
						event_global.mouseMove.x < (430 + 135) &&
						event_global.mouseMove.y > 250 &&
						event_global.mouseMove.y < (250 + 53)) {
						button_gamechoose.enable_hover_button();
						button_gamechoose.sprite_hover.setPosition(383, 266);
					}
					else if (event_global.mouseMove.x > 430 &&
						event_global.mouseMove.x < (430 + 135) &&
						event_global.mouseMove.y > 330 &&
						event_global.mouseMove.y < (330 + 53)) {
						button_gamechoose.enable_hover_button();
						button_gamechoose.sprite_hover.setPosition(383, 344);
					}
					else if (event_global.mouseMove.x > 430 &&
						event_global.mouseMove.x < (430 + 135) &&
						event_global.mouseMove.y > 410 &&
						event_global.mouseMove.y < (420 + 53)) {
						button_gamechoose.enable_hover_button();
						button_gamechoose.sprite_hover.setPosition(383, 422);
					}
					else {
						button_gamechoose.enable_normal_button();
					}
				}
				// control button of return-menu in hover state
				if (return_button.is_normal || return_button.is_hover) {
					if (event_global.mouseMove.x > 890 && event_global.mouseMove.x < (890 + 100) && event_global.mouseMove.y > 640 && event_global.mouseMove.y < (640 + 90)) {
						return_button.enable_hover_button();
					}
					else {
						return_button.enable_normal_button();
					}
				}
			}
			
			if (event_global.type == Event::MouseButtonPressed && event_global.mouseButton.button == Mouse::Left) {
				//mouse_count_clock_two = Mouse::getPosition(window);
				if (Mouse::getPosition(window).x > 890 && 
					Mouse::getPosition(window).x < (890 + 100) && 
					Mouse::getPosition(window).y > 640 && 
					Mouse::getPosition(window).y < (640 + 90)) {
					return_button.enable_down_button();
				}
				else if ( Mouse::getPosition(window).x > 430 &&
					 Mouse::getPosition(window).x < (430 + 135) &&
					 Mouse::getPosition(window).y > 174 &&
					 Mouse::getPosition(window).y < (174 + 53)) {
					button_gamechoose.enable_down_button();
					machine_number = 1;
				}
				else if ( Mouse::getPosition(window).x > 430 &&
					 Mouse::getPosition(window).x < (430 + 135) &&
					 Mouse::getPosition(window).y > 250 &&
					 Mouse::getPosition(window).y < (250 + 53)) {
					button_gamechoose.enable_down_button();
					machine_number = 2;
				}
				else if ( Mouse::getPosition(window).x > 430 &&
					 Mouse::getPosition(window).x < (430 + 135) &&
					 Mouse::getPosition(window).y > 330 &&
					 Mouse::getPosition(window).y < (330 + 53)) {
					button_gamechoose.enable_down_button();
					machine_number = 3;
				}
				else if ( Mouse::getPosition(window).x > 430 &&
					 Mouse::getPosition(window).x < (430 + 135) &&
					 Mouse::getPosition(window).y > 410 &&
					 Mouse::getPosition(window).y < (420 + 53)) {
					button_gamechoose.enable_down_button();
					machine_number = 4;
				}
			}
			if (event_global.type == Event::MouseButtonReleased && event_global.mouseButton.button == Mouse::Left) {
				//mouse_count_clock_two = Mouse::getPosition(window);
				if (Mouse::getPosition(window).x > 890 && Mouse::getPosition(window).x < (890 + 100) && Mouse::getPosition(window).y > 640 && Mouse::getPosition(window).y < (640 + 90)) {
					return_button.enable_diabled_button();
				}
			}
		
		}
		// when gameinfo
		if (gameinfo) {
			// change style
			if (event_global.type == sf::Event::EventType::KeyReleased && event_global.key.code == sf::Keyboard::A) {
				change_bg = true;
				if (globe_style_mode == 0) globe_style_mode = 1;
				else if (globe_style_mode == 1) globe_style_mode = 0;
			}
			if (event_global.type == sf::Event::MouseMoved) {
				// control button of return-menu in hover state
				if (return_button.is_normal || return_button.is_hover) {
					if (event_global.mouseMove.x > 890 && event_global.mouseMove.x < (890 + 100) && event_global.mouseMove.y > 640 && event_global.mouseMove.y < (640 + 90)) {
						return_button.enable_hover_button();
					}
					else {
						return_button.enable_normal_button();
					}
				}
				
				// control thanks button
				if (!gameinfo_thanks.is_down) {
					if (event_global.mouseMove.x > 459 && event_global.mouseMove.x < (459 + 80) && event_global.mouseMove.y > 445 && event_global.mouseMove.y < (445 + 136)) {
						if (gameinfo_thanks.is_normal) button_animate_count = 0;
						gameinfo_thanks.enable_hover_button();
					}
					else {
						gameinfo_thanks.enable_normal_button();
					}
				}
				// control gameinfo button
				if (!gameinfo_gameinfo.is_down) {
					if (event_global.mouseMove.x > 529 && event_global.mouseMove.x < (529 + 86) && event_global.mouseMove.y > 430 && event_global.mouseMove.y < (430 + 183)) {
						if (gameinfo_gameinfo.is_normal) button_animate_count = 0;
						gameinfo_gameinfo.enable_hover_button();
					}
					else {
						gameinfo_gameinfo.enable_normal_button();
					}
				}
				// control phaseinfo button
				if (!gameinfo_phaseinfo.is_down) {
					if (event_global.mouseMove.x > 603 && event_global.mouseMove.x < (603 + 86) && event_global.mouseMove.y > 430 && event_global.mouseMove.y < (430 + 183)) {
						if (gameinfo_phaseinfo.is_normal) button_animate_count = 0;
						gameinfo_phaseinfo.enable_hover_button();
					}
					else {
						gameinfo_phaseinfo.enable_normal_button();
					}
				}
				// control cardinfo button
				if (!gameinfo_cardinfo.is_down) {
					if (event_global.mouseMove.x > 673 && event_global.mouseMove.x < (673 + 86) && event_global.mouseMove.y > 430 && event_global.mouseMove.y < (430 + 183)) {
						if (gameinfo_cardinfo.is_normal) button_animate_count = 0;
						gameinfo_cardinfo.enable_hover_button();
					}
					else {
						gameinfo_cardinfo.enable_normal_button();
					}
				}
			}


			if (event_global.type == Event::MouseButtonPressed && event_global.mouseButton.button == Mouse::Left) {
				//mouse_count_clock_two = Mouse::getPosition(window);
				if (Mouse::getPosition(window).x > 890 && Mouse::getPosition(window).x < (890 + 100) && Mouse::getPosition(window).y > 640 && Mouse::getPosition(window).y < (640 + 90)) {
					return_button.enable_down_button();
				}
				// control thanks button
				else if (Mouse::getPosition(window).x > 459 && Mouse::getPosition(window).x < (459 + 80) && Mouse::getPosition(window).y > 445 && Mouse::getPosition(window).y < (445 + 136)) {
					gameinfo_thanks.enable_down_button();
					gameinfo_gameinfo.enable_normal_button();
					gameinfo_phaseinfo.enable_normal_button();
					gameinfo_cardinfo.enable_normal_button();

				}
				// control gameinfo button
				else if (Mouse::getPosition(window).x > 529 && Mouse::getPosition(window).x < (529 + 86) && Mouse::getPosition(window).y > 430 && Mouse::getPosition(window).y < (430 + 183)) {
					gameinfo_gameinfo.enable_down_button();
					gameinfo_phaseinfo.enable_normal_button();
					gameinfo_cardinfo.enable_normal_button();
					gameinfo_thanks.enable_normal_button();
				}
				// control phaseinfo button
				else if (Mouse::getPosition(window).x > 603 && Mouse::getPosition(window).x < (603 + 86) && Mouse::getPosition(window).y > 430 && Mouse::getPosition(window).y < (430 + 183)) {
					gameinfo_phaseinfo.enable_down_button();
					gameinfo_cardinfo.enable_normal_button();
					gameinfo_thanks.enable_normal_button();
					gameinfo_gameinfo.enable_normal_button();
				}
				// control cardinfo button
				else if (Mouse::getPosition(window).x > 673 && Mouse::getPosition(window).x < (673 + 86) && Mouse::getPosition(window).y > 430 && Mouse::getPosition(window).y < (430 + 183)) {
					gameinfo_cardinfo.enable_down_button();
					gameinfo_thanks.enable_normal_button();
					gameinfo_gameinfo.enable_normal_button();
					gameinfo_phaseinfo.enable_normal_button();
				}
			}
			if (event_global.type == Event::MouseButtonReleased && event_global.mouseButton.button == Mouse::Left) {
				mouse_count_clock_two = Mouse::getPosition(window);
				if (Mouse::getPosition(window).x > 890 && Mouse::getPosition(window).x < (890 + 100) && Mouse::getPosition(window).y > 640 && Mouse::getPosition(window).y < (640 + 90)) {
					return_button.enable_diabled_button();
				}
			}

		}
		// when game pause --only when game is running can it be enabled
		if (gamepause) {
			if (event_global.type == Event::MouseButtonPressed && event_global.mouseButton.button == Mouse::Left) {
				if (Mouse::getPosition(window).x > 222 && Mouse::getPosition(window).x < (222 + 110) && Mouse::getPosition(window).y > 288 && Mouse::getPosition(window).y < (288 + 70)) {
					pause_continue.enable_down_button();
				}
				else if (Mouse::getPosition(window).x > 163 && Mouse::getPosition(window).x < (163 + 230) && Mouse::getPosition(window).y > 365 && Mouse::getPosition(window).y < (365 + 70)) {
					pause_info.enable_down_button();
				}
				else if (Mouse::getPosition(window).x > 140 && Mouse::getPosition(window).x < (140 + 290) && Mouse::getPosition(window).y > 430 && Mouse::getPosition(window).y < (430 + 70)) {
					pause_return_menu.enable_down_button();
				}
			}
			if (event_global.type == Event::MouseButtonReleased && event_global.mouseButton.button == Mouse::Left) {
				if (Mouse::getPosition(window).x > 222 && Mouse::getPosition(window).x < (222 + 110) && Mouse::getPosition(window).y > 288 && Mouse::getPosition(window).y < (288 + 70)) {
					pause_continue.enable_diabled_button();
				}
				else if (Mouse::getPosition(window).x > 163 && Mouse::getPosition(window).x < (163 + 230) && Mouse::getPosition(window).y > 365 && Mouse::getPosition(window).y < (365 + 70)) {
					pause_info.enable_diabled_button();
				}
				else if (Mouse::getPosition(window).x > 140 && Mouse::getPosition(window).x < (140 + 290) && Mouse::getPosition(window).y > 430 && Mouse::getPosition(window).y < (430 + 70)) {
					pause_return_menu.enable_diabled_button();
				}
			}
			if (!pause_continue.is_down && !pause_info.is_down && !pause_return_menu.is_down) {
				if (event_global.type == sf::Event::MouseMoved)
				{
					// control button of cancel in hover state
					if (event_global.mouseMove.x > 222 && event_global.mouseMove.x < (222 + 110) && event_global.mouseMove.y > 288 && event_global.mouseMove.y < (288 + 70))
					{
						pause_continue.enable_hover_button();
					}
					else {
						pause_continue.enable_normal_button();
					}
					// control button of assure
					if (event_global.mouseMove.x > 163 && event_global.mouseMove.x < (163 + 230) && event_global.mouseMove.y > 365 && event_global.mouseMove.y < (365 + 70))
					{
						pause_info.enable_hover_button();
					}
					else {
						pause_info.enable_normal_button();
					}
					// control button of discard in hover state
					if (event_global.mouseMove.x > 140 && event_global.mouseMove.x < (140 + 290) && event_global.mouseMove.y > 430 && event_global.mouseMove.y < (430 + 70))
					{
						pause_return_menu.enable_hover_button();
					}
					else {
						pause_return_menu.enable_normal_button();
					}
				}
			}
		}

		// human operate of gameover
		if (gameover) {
			if (event_global.type == sf::Event::MouseMoved) {
				// control button of return-menu in hover state
				if (return_menu.is_normal || return_menu.is_hover) {
					if (event_global.mouseMove.x > 820 && event_global.mouseMove.x < (820 + 100) && event_global.mouseMove.y > 300 && event_global.mouseMove.y < (300 + 200)) {
						return_menu.enable_hover_button();
					}
					else {
						return_menu.enable_normal_button();
					}
				}
			}

			if (event_global.type == Event::MouseButtonPressed && event_global.mouseButton.button == Mouse::Left) {
				//mouse_count_clock_two = Mouse::getPosition(window);
				if (Mouse::getPosition(window).x > 820 && Mouse::getPosition(window).x < (820 + 100) && Mouse::getPosition(window).y > 300 && Mouse::getPosition(window).y < (300 + 200)) {
					return_menu.enable_down_button();
				}
			}
			if (event_global.type == Event::MouseButtonReleased && event_global.mouseButton.button == Mouse::Left) {
				//mouse_count_clock_two = Mouse::getPosition(window);
				if (Mouse::getPosition(window).x > 820 && Mouse::getPosition(window).x < (820 + 100) && Mouse::getPosition(window).y > 300 && Mouse::getPosition(window).y < (300 + 200)) {
					return_menu.enable_diabled_button();
				}
			}
		}

		if (gamerun) {

			// change image
			if (event_global.type == sf::Event::EventType::KeyReleased && event_global.key.code == sf::Keyboard::A) {
				if (img_bg_number == bg_max_no) img_bg_number = 0;
				else img_bg_number++;
				change_bg = true;
			}

			if (event_global.type == Event::MouseButtonPressed && event_global.mouseButton.button == Mouse::Left) {

				send_packet("MSG", name, " i clicked", &socket);
				mouse_count_clock_two = Mouse::getPosition(window);
				if (mouse_count_clock_two.x > 807 && mouse_count_clock_two.x < (807 + 61) && mouse_count_clock_two.y > 604 && mouse_count_clock_two.y < (604 + 75) && !button_ok.is_disabled)
				{ // the button of ok //(807, 604)++(61,75)
					button_ok.enable_down_button();
				}
				else if (mouse_count_clock_two.x > 807 && mouse_count_clock_two.x < (807 + 61) && mouse_count_clock_two.y > 694 && mouse_count_clock_two.y < (694 + 73) && !button_cancel.is_disabled)
				{ // the button of cancel //(807, 604)++(61,75)  
					button_cancel.enable_down_button();
				}
				else if (mouse_count_clock_two.x > 874 && mouse_count_clock_two.x < (874 + 33) && mouse_count_clock_two.y > 644 && mouse_count_clock_two.y < (644 + 81) && !button_discard.is_disabled)
				{ // the button of discard //(807, 604)++(61,75)  
					button_discard.enable_down_button();
				}
				else if (mouse_count_clock_two.x > 0 && mouse_count_clock_two.x < (0 + 255) && mouse_count_clock_two.y > 0 && mouse_count_clock_two.y < (0 + 70) && !button_discard.is_disabled)
				{ // the button of discard //(807, 604)++(61,75)  
					pause_button.enable_down_button();
				}
			}
			if (event_global.type == Event::MouseButtonReleased && event_global.mouseButton.button == Mouse::Left) {
				mouse_count_clock_one = Mouse::getPosition(window);
				//bool card_selected = Human.cards.Search_Card_Position(mouse_count_clock_one);
				mouse_click_timer.restart();
				if (Mouse::getPosition(window).x > 0 && Mouse::getPosition(window).x < (0 + 265) && Mouse::getPosition(window).y > 0 && Mouse::getPosition(window).y < (0 + 80)) {
					pause_button.enable_diabled_button();
				}
				return mouse_count_clock_one;
			}

			if (event_global.type == sf::Event::MouseMoved)
			{
				// control button of cancel in hover state
				if (!button_cancel.is_disabled) {
					if (event_global.mouseMove.x > 807 && event_global.mouseMove.x < (807 + 61) && event_global.mouseMove.y > 694 && event_global.mouseMove.y < (694 + 73))
					{ 
						button_cancel.enable_hover_button();
					}
					else {
						button_cancel.enable_normal_button();
					}
				}
				// control button of assure
				if (!button_ok.is_disabled) {
					if (event_global.mouseMove.x > 807 && 
						event_global.mouseMove.x < (807 + 61) && 
						event_global.mouseMove.y > 604 && 
						event_global.mouseMove.y < (604 + 75))
					{
						button_ok.enable_hover_button();
					}
					else {
						button_ok.enable_normal_button();
					}
				}
				// control button of discard in hover state
				if (!button_discard.is_disabled) {
					if (event_global.mouseMove.x > 874 && 
						event_global.mouseMove.x < (874 + 33) && 
						event_global.mouseMove.y > 644 && 
						event_global.mouseMove.y < (644 + 81))
					{ 
						button_discard.enable_hover_button();
					}
					else {
						button_discard.enable_normal_button();
					}
				}
			    
				if (event_global.mouseMove.x > 0 && 
					event_global.mouseMove.x < (0 + 255) && 
					event_global.mouseMove.y >0 && 
					event_global.mouseMove.y < (0 + 70))
				{
					pause_button.enable_hover_button();
				}
				else
				{
					pause_button.enable_normal_button();
				}
			}
			
		}
	}
	return virtual_vector;
}
