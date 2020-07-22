#include "Game.h"
void Game::NET_Human_Round_Initialize() {

	// human get 2 cards each time is its round
	if (Human.round_draw_phase) {

		// insert two card......

		// set basic value
		Human.kill_times = 0;    // set original kill number is 0 when a new round start
		Human.drank_analeptic = false;   // each round no use analeptic
		Human.round_draw_phase = false;
	
		sf::Packet pack;
		pack << "Draw_Over" << Human.location_code;
		(&socket)->send(pack);
	}
}

void Game::NET_Human_Round_enable_dying_state() {
	if (Human.HP <= 0) {
		Human.is_dying = true;
	}
	if (Human.is_dying == true) {
		/*------------>>operate in server ----------*/
// 		// sent begging for peach signal to other machines(all of them)
// 		for (int number=0; number < machine_number; number++) {
// 			Machine[number].skill.begging_peach = true;
// 		}
// 		exturn = turn; /// alaso ==>>  exturn=Human.charactor_code;
// 		//cout << exturn << endl;
// 		//cout << "攻击者为：" << turn<<endl;
// 		round_loop_starter = turn;
// 		peach_begger = Human.charactor_code;
// 		//Insert_Message(L"人类玩家 濒死求桃 X(");
	}
}

int Game::NET_Human_Round_Skill_Judgment(Vector2i mouse_select_vector) {

	// about peach beg

	// skill judgment

	// end-up skill of amazing grace

	if (Human.skill.amazing_grace_state){
		// set no card enable to play
		Single_Card* ptr = Human.cards.Pile_Card_Total->next;
		for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {
			ptr->enable_to_play = false;
			ptr = ptr->next;
		}

		if (temp_pile.Search_Card_Position(mouse_select_vector)) {
			ptr = temp_pile.Search_Card_Position_locate(mouse_select_vector);
			if (ptr->mouse_select_card == false && Human.select_card == false) {
				ptr->mouse_select_card = true;
				Human.select_card = true;
				button_ok.enable_normal_button();
			}
			else if (ptr->mouse_select_card == true && Human.select_card == true) {
				ptr->mouse_select_card = false;
				Human.select_card = false;
				button_ok.enable_diabled_button();
			}
		}
		if (Human.select_card == true) {
			button_discard.enable_diabled_button();
			ptr = temp_pile.Pile_Card_Total->next;
			while (ptr != NULL) {
				if (ptr->mouse_select_card) break;
				ptr = ptr->next;
			}
			if (button_ok.is_down) {
				// result operate in server
				
				// initialize data
				Human.select_card = false;
				Human.selecet_card_amount = 0;
				//human_defense = false;

				// skill state 
				Human.skill.amazing_grace_state = false;
				// change button unable
				button_ok.enable_diabled_button();
				button_cancel.enable_diabled_button();
				// show message box
				//Insert_Message(L"人类玩家 获得一张牌！");
				// reset all card unselected
				ptr = Human.cards.Pile_Card_Total->next;
				while (ptr) {
					ptr->mouse_select_card = false;
					ptr = ptr->next;
				}
				return 0;
			}
		}
		button_discard.enable_diabled_button();
		return 0;
	}
	
	if (Human.skill.need_jink || Human.skill.defense_analeptic_kill) {
		if (button_cancel.is_disabled && button_ok.is_disabled && button_discard.is_disabled)
			button_cancel.enable_normal_button();
		// set jink card enable to play
		Single_Card* ptr = Human.cards.Pile_Card_Total->next;
		for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {
			switch (ptr->card_info.single_card_number) {
			case jink:
				ptr->enable_to_play = true;
				break;
			default:
				ptr->enable_to_play = false;
				break;
			}
			ptr = ptr->next;
		}
		if (Human.cards.Search_Card_Position(mouse_select_vector)) {
			Single_Card* ptr = nullptr;
			ptr = Human.cards.Search_Card_Position_locate(mouse_select_vector);
			if (ptr->enable_to_play) {
				if (ptr->mouse_select_card == false && Human.select_card == false) {
					ptr->mouse_select_card = true;
					Human.select_card = true;
					button_ok.enable_normal_button();
					button_cancel.enable_normal_button();
				}
				else if (ptr->mouse_select_card == true && Human.select_card == true) {
					ptr->mouse_select_card = false;
					Human.select_card = false;
					button_ok.enable_diabled_button();
					button_cancel.enable_normal_button();
				}
			}
		}
		if (Human.select_card == true) {

			if (button_ok.is_down) {
				// result  operate in server 
				sf::Packet pack_jink;
				pack_jink << "Defense_Reply" << Human.location_code << "jink";
				(&socket)->send(pack_jink);
				// initialize data
				Human.select_card = false;
				Human.selecet_card_amount = 0;
				//human_defense = false;
				Human.skill.need_jink = false;
				Human.skill.defense_analeptic_kill = false;
				// animator go operate in server to display to all client
				sf::Packet pack_animator;
				pack_animator << "Animation" << Human.location_code << "jink";
				(&socket)->send(pack_animator);
				// change button unable
				button_ok.enable_diabled_button();
				button_cancel.enable_diabled_button();
				button_discard.enable_diabled_button();
				// show message box
				//Insert_Message(L"人类玩家 出 闪 抵抗！");
				return 0;
			}
		}
		if (button_cancel.is_down) {
			// result  operate in server
			sf::Packet pack_damage;
			if (Human.skill.defense_analeptic_kill)
				pack_damage << "Defense_Reply" << Human.location_code << "damage"<<"double_kill";
			else if (Human.skill.need_jink) 
				pack_damage << "Defense_Reply" << Human.location_code << "damage"<<"single_kill";

			(&socket)->send(pack_damage);

			// show message
/*			Insert_Message(L"人类玩家 HP 减少了！");*/

			// judge human is dying?
			// NET_Human_Round_enable_dying_state();
			// find node that is chose card
			Single_Card* ptr = Human.cards.Pile_Card_Total->next;
			for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {
				if (ptr->mouse_select_card) break;
				ptr = ptr->next;
			}
			if (ptr != nullptr)
			{
				ptr->mouse_select_card = false;
			}
			// initialize data
			Human.select_card = false;
			Human.selecet_card_amount = 0;
			//if(Human.HP>0)  exturn = normal;
			Human.skill.need_jink = false;
			Human.skill.defense_analeptic_kill = false;
			// animator go
			sf::Packet pack_animator;
			pack_animator << "Animation" << Human.location_code << "damage";
			(&socket)->send(pack_animator);
			// change button unable
			button_ok.enable_diabled_button();
			button_cancel.enable_diabled_button();
			button_discard.enable_diabled_button();
			return 0;
		}
		return 0;
	}	
	if (Human.skill.begging_peach) {
		if (button_cancel.is_disabled && button_ok.is_disabled && button_discard.is_disabled)
			button_cancel.enable_normal_button();
		//dying_loop = true;
		Single_Card* ptr = Human.cards.Pile_Card_Total->next;
		for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {
			switch (ptr->card_info.single_card_number) {
			case peach:
				ptr->enable_to_play = true;
				break;
			default:
				ptr->enable_to_play = false;
				break;
			}
			ptr = ptr->next;
		}
		if (Human.cards.Search_Card_Position(mouse_select_vector)) {
			Single_Card* ptr = nullptr;
			ptr = Human.cards.Search_Card_Position_locate(mouse_select_vector);
			if (ptr->enable_to_play) {
				if (ptr->mouse_select_card == false && Human.select_card == false) {
					ptr->mouse_select_card = true;
					Human.select_card = true;
					button_ok.enable_normal_button();
					button_cancel.enable_normal_button();
				}
				else if (ptr->mouse_select_card == true && Human.select_card == true) {
					ptr->mouse_select_card = false;
					Human.select_card = false;
					button_ok.enable_diabled_button();
					button_cancel.enable_normal_button();
				}
			}
		}
		if (Human.select_card == true) {
			if (button_ok.is_down) {
				// find node that is chose card
				Single_Card* ptr = Human.cards.Pile_Card_Total->next;
				for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {
					if (ptr->mouse_select_card) break;
					ptr = ptr->next;
				}
				// result --------operate in server 
				sf::Packet pack_give_peach;
				pack_give_peach << "Defense_Reply" << Human.location_code << "give_peach";
				(&socket)->send(pack_give_peach);
				// pile card change  operate in server
				Human.skill.begging_peach = false;
				// initialize data
				Human.select_card = false;
				Human.selecet_card_amount = 0;
				// change button unable
				button_ok.enable_diabled_button();
				button_cancel.enable_diabled_button();
				button_discard.enable_diabled_button();
				return 0;
			}
		}
		if (button_cancel.is_down) {
			// result  operate in server 

			sf::Packet pack_reject_peach;
			pack_reject_peach << "Defense_Reply" << Human.location_code << "reject_peach";
			(&socket)->send(pack_reject_peach);
			// set defense skill unable
			Human.skill.begging_peach = false;
			// find node that is chose card
			Single_Card* ptr = Human.cards.Pile_Card_Total->next;
			for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {
				if (ptr->mouse_select_card) break;
				ptr = ptr->next;
			}
			if (ptr != nullptr)
			{
				ptr->mouse_select_card = false;
			}
			// initialize data
			Human.select_card = false;
			Human.selecet_card_amount = 0;
			// animator go
			// change button unable
			button_ok.enable_diabled_button();
			button_cancel.enable_diabled_button();
			button_discard.enable_diabled_button();
			// show message 
			//Insert_Message(L"人类玩家 拒绝出桃");
			return 0;
		}
		return 0;
	}

	// dying & self_save
	if (Human.self_save) {
		if (button_cancel.is_disabled && button_ok.is_disabled && button_discard.is_disabled)
			button_cancel.enable_normal_button();
		Single_Card* ptr = Human.cards.Pile_Card_Total->next;
		for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {
			switch (ptr->card_info.single_card_number) {
			case peach:
				ptr->enable_to_play = true;
				break;
			case analeptic:
				ptr->enable_to_play = true;
				break;
			default:
				ptr->enable_to_play = false;
				break;
			}
			ptr = ptr->next;
		}
		if (Human.cards.Search_Card_Position(mouse_select_vector)) {
			Single_Card* ptr = nullptr;
			ptr = Human.cards.Search_Card_Position_locate(mouse_select_vector);
			if (ptr->enable_to_play) {
				if (ptr->mouse_select_card == false && Human.select_card == false) {
					ptr->mouse_select_card = true;
					Human.select_card = true;
					button_ok.enable_normal_button();
					button_cancel.enable_normal_button();
				}
				else if (ptr->mouse_select_card == true && Human.select_card == true) {
					ptr->mouse_select_card = false;
					Human.select_card = false;
					button_ok.enable_diabled_button();
					button_cancel.enable_normal_button();
				}
			}
		}
		if (Human.select_card == true) {
			if (button_ok.is_down) {
				Human.self_save = false;
				// find node that is chose card
				Single_Card* ptr = Human.cards.Pile_Card_Total->next;
				for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {
					if (ptr->mouse_select_card) break;
					ptr = ptr->next;
				}
				// animator go----server
				sf::Packet pack_animator;
				if (ptr->card_info.single_card_number == peach)
					pack_animator << "Animation" << Human.location_code << "peach";
				else if (ptr->card_info.single_card_number == analeptic)
					pack_animator << "Animation" << Human.location_code << "analeptic";
				(&socket)->send(pack_animator);
				// result  operate in server
				sf::Packet pack_selfsave;
				pack_selfsave << "Defense_Reply" << Human.location_code << "selfsave"<< ptr->card_info.single_card_number;
				(&socket)->send(pack_selfsave);
				// initialize data
				Human.select_card = false;
				Human.selecet_card_amount = 0;
				// change button unable
				button_ok.enable_diabled_button();
				button_cancel.enable_diabled_button();
				button_discard.enable_diabled_button();
				return 0;
			}
		}
		if (button_cancel.is_down) {
			// result ---server

			sf::Packet pack_selfsave;
			pack_selfsave << "Defense_Reply" << Human.location_code << "reject_selfsave";
			(&socket)->send(pack_selfsave);
			// set self-saving state unable
 			Human.self_save = false;
			// find node that is chose card
			Single_Card* ptr = Human.cards.Pile_Card_Total->next;
			for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {
				if (ptr->mouse_select_card) break;
				ptr = ptr->next;
			}
			if (ptr != nullptr)
			{
				ptr->mouse_select_card = false;
			}
			// initialize data
			Human.select_card = false;
			Human.selecet_card_amount = 0;
			// animator go
			// change button unable
			button_ok.enable_diabled_button();
			button_cancel.enable_diabled_button();
			button_discard.enable_diabled_button();
			return 0;
		}
	}

	return 1;
}
void Game::NET_Human_Round() {
	Vector2i mouse_select_vector=Input();;  // in general there only exist one input function  * wtf! that is matter most
	//
	NET_Human_Round_Initialize();
	if(NET_Human_Round_Skill_Judgment(mouse_select_vector)==0) return;

	// Human play card---judge in server
	if (Human.round_play_phase) {
		// set each card enable to play or cant 
		Single_Card* ptr = nullptr;
		ptr = Human.cards.Pile_Card_Total->next;
		for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {
			switch (ptr->card_info.single_card_number) {
			case kill:
				if (Human.kill_times < Human.kill_limit) ptr->enable_to_play = true;
				else  ptr->enable_to_play = false;
				break;
			case jink:
				ptr->enable_to_play = false;
				break;
			case analeptic:
				if (Human.drank_analeptic)	ptr->enable_to_play = false;
				else	ptr->enable_to_play = true;
				break;
			case peach:
				ptr->enable_to_play = true;
				break;
			case amazing_grace:
				ptr->enable_to_play = true;
				break;
			case nullification:
				ptr->enable_to_play = false;
				break;
			default:
				break;
			}
			ptr = ptr->next;
		}
		// button stage initialize
		if ((Human.select_card == false) && !(button_discard.is_hover || button_discard.is_down)) { // there exist tow kind of situation -- original initialize and no hover & no down
			button_ok.enable_diabled_button();
			button_cancel.enable_diabled_button();
			button_discard.enable_normal_button();
		}
		if (Human.cards.Search_Card_Position(mouse_select_vector)) {        //play choose cards ,only once each time   also  it can change button state according to card attribute
			Single_Card* ptr = nullptr;
			ptr = Human.cards.Search_Card_Position_locate(mouse_select_vector);
			if (ptr->enable_to_play) {
				if (ptr->mouse_select_card == false && Human.select_card == false) {
					ptr->mouse_select_card = true;
					Human.select_card = true;
					if (ptr->card_info.can_attck) {
						button_ok.enable_diabled_button();
						button_cancel.enable_normal_button();
						button_discard.enable_diabled_button();
					}
					else {
						button_ok.enable_normal_button();
						button_cancel.enable_normal_button();
						button_discard.enable_diabled_button();
					}
				}
				else if (ptr->mouse_select_card == true && Human.select_card == true) {
					ptr->mouse_select_card = false;
					Human.select_card = false;
					Machine[0].being_choose = false;
					Machine[1].being_choose = false;
					Machine[2].being_choose = false;
					Machine[3].being_choose = false;
				}
				return;   // once select one card, return to draw  ?that is needed?
			}
		}
		if (Human.select_card) {
			// find node which card is chosen
			Single_Card* ptr = Human.cards.Pile_Card_Total->next;
			for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {
				if (ptr->mouse_select_card) break;
				ptr = ptr->next;
			}
			if (ptr != NULL && ptr->card_info.can_attck) {    // if the select card then choose enemy  (window_width - 143) / 2, 40 // 宽 143 || 高 195
				// machine-0 to machine-3 Traverse each situation;though it seem a little bit inefficient;looking for further improvement
				for (int number = 0; number < machine_number; number++) {
					if (mouse_select_vector.x > Machine[number].location_one.x && 
						mouse_select_vector.x < Machine[number].location_two.x &&
						mouse_select_vector.y > Machine[number].location_one.y && 
						mouse_select_vector.y < Machine[number].location_two.y && 
						Machine[number].being_choose == false &&
						Human.chosen_number==0) {     // when it tends to choose enemy
						Machine[number].being_choose = true;
						button_ok.enable_normal_button();
						button_cancel.enable_diabled_button();
						button_discard.enable_diabled_button();
						Human.chosen_number = 1;
					}
					else if (mouse_select_vector.x > Machine[number].location_one.x && 
						mouse_select_vector.x < Machine[number].location_two.x && 
						mouse_select_vector.y>Machine[number].location_one.y && 
						mouse_select_vector.y < Machine[number].location_two.y && 
						Machine[number].being_choose == true) {       // when it tends to cancel choose
						Machine[number].being_choose = false;
						button_ok.enable_diabled_button();
						button_cancel.enable_normal_button();
						button_discard.enable_diabled_button();
						Human.chosen_number = 0;
					}
					else if (mouse_select_vector.x > 807 &&
						mouse_select_vector.x < (807 + 61) &&
						mouse_select_vector.y > 604 && 
						mouse_select_vector.y < (604 + 75) &&
						Machine[number].being_choose == true) {  // when it choose enemy & tends to click assure button to fight   the assure button area is 
						Machine[number].being_choose = false;
						if (ptr->card_info.single_card_number == kill && Human.drank_analeptic) {

							cout << "analeptic__killllit:::" << number << endl;
							//  animator running ---server
							sf::Packet pack_animator;
							pack_animator << "Animation" << Human.location_code<<"kill";
							(&socket)->send(pack_animator);
							// result
							Human.kill_times++;
							// play it to apply in other ---operate in server
							sf::Packet pack;							
							switch (number)
							{
							case 0:
								pack << "Play_Card" << Human.location_code << "analeptic_kill" << Machine[0].location_code;
								break;
							case 1:
								pack << "Play_Card" << Human.location_code << "analeptic_kill" << Machine[1].location_code;
								break;
							case 2:
								pack << "Play_Card" << Human.location_code << "analeptic_kill" << Machine[2].location_code;
								break;
							case 3:
								pack << "Play_Card" << Human.location_code << "analeptic_kill" << Machine[3].location_code;
								break;
							}
							(&socket)->send(pack);
						}
						else if (ptr->card_info.single_card_number == kill)
						{
							//  animator running
							cout << "__killllit:::" << number << endl;
							sf::Packet pack_animation;
							pack_animation << "Animation" << Human.location_code << "kill";
							(&socket)->send(pack_animation);
							// result 
							Human.kill_times++;
							// set state in server then update it to achieve skill
							sf::Packet pack;
							switch (number)
							{
							case 0:
								pack << "Play_Card" << Human.location_code << "kill" << Machine[0].location_code;
								break;
							case 1:
								pack << "Play_Card" << Human.location_code << "kill" << Machine[1].location_code;
								break;
							case 2:
								pack << "Play_Card" << Human.location_code << "kill" << Machine[2].location_code;
								break;
							case 3:
								pack << "Play_Card" << Human.location_code << "kill" << Machine[3].location_code;
								break;
							}
							(&socket)->send(pack);
						}
						Human.chosen_number = 0;
						Human.select_card = false;
						// change select state
						Machine[0].being_choose = false;
						Machine[1].being_choose = false;
						Machine[2].being_choose = false;
						Machine[3].being_choose = false;
						Human.chosen_number = 0;
						Human.select_card = false;
						// then change button state
						button_ok.enable_diabled_button();
						button_cancel.enable_diabled_button();
						button_discard.enable_diabled_button();
						return;
					}
				}
			}
			else {
				if (mouse_select_vector.x > 807 && mouse_select_vector.x < (807 + 61) && mouse_select_vector.y > 604 && mouse_select_vector.y < (604 + 75)) {  // when it play card & the card is non_choosen   the assure button area is 
					if (ptr->card_info.single_card_number == peach) {
						// animation go
						sf::Packet pack_animator;
						pack_animator << "Animation" << Human.location_code << "peach";
						(&socket)->send(pack_animator);
						// sent pack to change state & update cards & HP
						sf::Packet pack;
						pack << "Play_Card" << Human.location_code << "peach";
						(&socket)->send(pack);
					}
					else if (ptr->card_info.single_card_number == analeptic) { // when human have not die,this kill can doubled kill power
						// result
						Human.kill_power++;
						Human.drank_analeptic = true;
						// animation go in every client
						sf::Packet pack_animator;
						pack_animator << "Animation" << Human.location_code << "analeptic";
						(&socket)->send(pack_animator);
						// send pack to update cards piles
						sf::Packet pack;
						pack << "Play_Card" << Human.location_code << "analeptic";
						(&socket)->send(pack);
					}
					else if (ptr->card_info.single_card_number == amazing_grace) { // get anyone a card
						// round turn
						sf::Packet pack;
						pack << "Play_Card" << Human.location_code << "amazing_grace";
						(&socket)->send(pack);
                        // button initialize
						button_discard.enable_diabled_button();
						button_cancel.enable_diabled_button();
						button_ok.enable_diabled_button();
					}
					Machine[0].being_choose = false;
					Machine[1].being_choose = false;
					Machine[2].being_choose = false;
					Machine[3].being_choose = false;
					Human.chosen_number = 0;
					Human.select_card = false;
					// then change button state
					button_ok.enable_diabled_button();
					button_cancel.enable_diabled_button();
					button_discard.enable_normal_button();

				}
			}
			if (mouse_select_vector.x > 807 && mouse_select_vector.x < (807 + 61) && mouse_select_vector.y > 694 && mouse_select_vector.y < (694 + 73)&&!button_cancel.is_disabled) {  // when it go to cancel ,change all anyway
				Machine[0].being_choose = false;
				Machine[1].being_choose = false;
				Machine[2].being_choose = false;
				Machine[3].being_choose = false;
				Human.chosen_number = 0;
				Human.select_card = false;
				ptr->mouse_select_card = false;
				// then change button state
				button_ok.enable_diabled_button();
				button_cancel.enable_diabled_button();
				button_discard.enable_normal_button();
			}
			return;
		}
		if (mouse_select_vector.x > 874 && mouse_select_vector.x < (874 + 33) && mouse_select_vector.y > 644 && mouse_select_vector.y < (644 + 81)) {
			// operate in server...
			sf::Packet pack;
			pack << "Play_Over" << Human.location_code;
			(&socket)->send(pack);
		}
	}
	// Human discard
	if (Human.round_discard_phase) {
		// there exist tow kind of situation -- original initialize and no hover & no down
		if (Human.cards.Pile_Card_Amount <= Human.HP) {   // no need to discard
			button_ok.enable_diabled_button();
			button_cancel.enable_diabled_button();
			button_discard.enable_diabled_button();
			/*--------->> operate in server*/
			sf::Packet pack;
			pack << "Discard_Over" << Human.location_code;
			(&socket)->send(pack);
			return;
		}
		else if (Human.selecet_card_amount < Human.cards.Pile_Card_Amount - Human.HP) {
			// discard normal button set
			button_ok.enable_diabled_button();
			button_cancel.enable_diabled_button();
			button_discard.enable_diabled_button();
		}
		else if (button_ok.is_disabled)	button_ok.enable_normal_button();

		if (Human.cards.Search_Card_Position(mouse_select_vector)) {
			Single_Card* ptr = nullptr;
			ptr = Human.cards.Search_Card_Position_locate(mouse_select_vector);
			if (ptr->mouse_select_card == false && Human.selecet_card_amount < Human.cards.Pile_Card_Amount - Human.HP) {  // only select limited cards
				ptr->mouse_select_card = true;
				Human.selecet_card_amount++;
			}
			else if (ptr->mouse_select_card == true) {
				ptr->mouse_select_card = false;
				Human.selecet_card_amount--;
			}
		}
		if (button_ok.is_down) {
			/*--------->> operate in server*/
			int temp_delete_number;
			// find that card
			LinkList ptr = Human.cards.Pile_Card_Total->next;
			while (ptr) {
				if (ptr->mouse_select_card == true) {
					temp_delete_number = ptr->card_info.single_card_number;
					// if card select send message to delete card
					sf::Packet pack;
					pack << "Discard_Card" << Human.location_code << temp_delete_number;
					(&socket)->send(pack);
				}
				ptr = ptr->next;
			}
			// send end-up signal to refresh cards in all clients
			sf::Packet pack_end_discard;
			pack_end_discard << "Discard_Card" << Human.location_code << -2;
			(&socket)->send(pack_end_discard);
			Human.selecet_card_amount = 0;
			button_ok.enable_diabled_button();
			// change state in server
			sf::Packet pack;
			pack << "Discard_Over" << Human.location_code;
			(&socket)->send(pack);
		}
	}
	// button unable when animator start & go
	if (animator_running) {
		button_ok.enable_diabled_button();
		button_cancel.enable_diabled_button();
		button_discard.enable_diabled_button();
	}
}