#include "Game.h"
void Game::Human_Round_Initialize() {
	if (piles.Pile_Card_Amount < 10) {
		Single_Card* ptr = discard_pile.Pile_Card_Total->next;
		while (ptr){
			ptr = ptr->next;
			int card_number;
			card_number = discard_pile.Pile_Card_Total->next->card_info.single_card_number;
			discard_pile.Delete_Card(card_number);
			piles.Insert_Card(card_number, rand()%4);
		}
		Insert_Message(L">>>>>>>>>>>牌堆洗牌<<<<<<<<<<<<<");
	}
	// human get 2 cards each time is its round
	if (Human.round_draw_phase) {
		Insert_Message(L"————人类玩家-----回合开始————");
		for (int i = 0; i < 2; i++) {
			Human.cards.Insert_Card(piles.Pile_Card_Total->next->card_info.single_card_number, piles.Pile_Card_Total->next->card_info.suit);
			Human.cards.Get_Node(Human.cards.Pile_Card_Amount - 1)->mouse_select_card = false;
			piles.Delete_Card(piles.Pile_Card_Total->next->card_info.single_card_number);
		}
		Insert_Message(L" 人类玩家 摸了 2 张牌");
		// original position set
		Single_Card* ptr = Human.cards.Pile_Card_Total->next;
		for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {  // each card:  width 93 || height 130
			ptr->point_one.x = 165 + i * 93;
			ptr->point_one.y = window_height - 135;
			ptr->point_two.x = 165 + (i + 1) * 93;
			ptr->point_two.y = window_height - 135 + 130;
			ptr = ptr->next;
		}
		Human.kill_times = 0;    // set original kill number is 0 when a new round start
		Human.drank_analeptic = false;   // each round no use analeptic
		Human.round_draw_phase = false;
	}
	// to update player's card with card_texture,card_sprite,card_vector where there add new card in * or update card info
	Single_Card* ptr = Human.cards.Pile_Card_Total->next;
	for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {
		if (!ptr->file_loaded) {
			stringstream ss;
			ss << "image/skill&equip_card/small_card/" << ptr->card_info.single_card_number << ".jpg";
			Load_Image(ptr->texture_card, ptr->sprite_card, ss.str(), 0, 0, 1, 1);
			ptr->file_loaded = true;
		}
		ptr->enable_to_play = false;
		ptr = ptr->next;
	}
	if (Human.HP > 0 && Human.is_dying ) {
		Human.is_dying = false;
		Human.die = false;
		Human.self_save = false;
		exturn = normal;
	}
}

void Game::Human_Round_enable_dying_state() {
	if (Human.HP <= 0) {
		Human.is_dying = true;
	}
	if (Human.is_dying == true) {
		// sent begging for peach signal to other machines(all of them)
		for (int number=0; number < machine_number; number++) {
			Machine[number].skill.begging_peach = true;
		}
		exturn = turn; /// alaso ==>>  exturn=Human.charactor_code;
		//cout << exturn << endl;
		//cout << "攻击者为：" << turn<<endl;
		round_loop_starter = turn;
		peach_begger = Human.charactor_code;
		Insert_Message(L"人类玩家 濒死求桃 X(");
	}
}

int Game::Human_Round_Skill_Judgment(Vector2i mouse_select_vector) {

	// about begger-life
	if (Human.skill.begging_peach == false && dying_loop && round_loop_starter == human) {
		switch (peach_begger)
		{
		case human:
			if (Human.HP <= 0) Human.die = true;
			break;
		case machine_0:
			if (Machine[0].HP <= 0) {
				Machine[0].die = false;
				Machine[0].skill.begging_peach = false;
				Machine[0].self_save = false;
				Machine[0].HP = 2;
				Machine[0].limited_HP = 2;
				Insert_Message(L"求助失败！电脑-1 重生了！");
				Human.killing_number++;
			}
			break;
		case machine_1:
			if (Machine[1].HP <= 0) {
				Machine[1].die = false;
				Machine[1].skill.begging_peach = false;
				Machine[1].self_save = false;
				Machine[1].HP = 2;
				Machine[1].limited_HP = 2;
				Insert_Message(L"求助失败！电脑-2 重生了！");
				Human.killing_number++;
			}
			break;
		case machine_2:
			if (Machine[2].HP <= 0) {
				Machine[2].die = false;
				Machine[2].skill.begging_peach = false;
				Machine[2].self_save = false;
				Machine[2].HP = 2;
				Machine[2].limited_HP = 2;
				Insert_Message(L"求助失败！电脑-3 重生了！");
				Human.killing_number++;
			}
			break;
		case machine_3:
			if (Machine[3].HP <= 0) {
				Machine[3].die = false;
				Machine[3].skill.begging_peach = false;
				Machine[3].self_save = false;
				Machine[3].HP = 2;
				Machine[3].limited_HP = 2;
				Insert_Message(L"求助失败！电脑-4 重生了！");
				Human.killing_number++;
			}
			break;
		default:
			break;
		}
		dying_loop = false;
		round_loop_starter = -1; // default value is -1 to escape & found unknown error
		exturn = normal;
		exturn_backup = -1;
		// reset peach-begging to default false
		Human.skill.begging_peach = false;
		Machine[0].skill.begging_peach = false;
		Machine[1].skill.begging_peach = false;
		Machine[2].skill.begging_peach = false;
		Machine[3].skill.begging_peach = false;
		return 0;
	}
	// skill judgment


	// end-up skill of amazing grace
	if (Human.skill.amazing_grace_state == false && amazing_grace_loop && round_loop_starter == human) {
		temp_pile.clear();
		// reset all skill signal
		Human.skill.amazing_grace_state = false;
		Machine[0].skill.amazing_grace_state = false;
		Machine[1].skill.amazing_grace_state = false;
		Machine[2].skill.amazing_grace_state = false;
		Machine[3].skill.amazing_grace_state = false;
		// reset 
		amazing_grace_loop = false;
		round_loop_starter = -1;
		exturn = normal;
		exturn_backup = -1;
	}
    
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
				// result
				Human.cards.Insert_Card(ptr->card_info.single_card_number, 1);
				temp_pile.Delete_Card_Selected();
				// initialize data
				Human.select_card = false;
				Human.selecet_card_amount = 0;
				//human_defense = false;
				if (exturn == machine_number + 1) exturn = human;  // meaning going to a loop
				else exturn++;
				// skill state 
				Human.skill.amazing_grace_state = false;
				// change button unable
				button_ok.enable_diabled_button();
				button_cancel.enable_diabled_button();
				// show message box
				Insert_Message(L"人类玩家 获得一张牌！");
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
				// result
				Human.cards.Delete_Card_Selected();
				discard_pile.Insert_Card(jink, 1);
				// initialize data
				Human.select_card = false;
				Human.selecet_card_amount = 0;
				//human_defense = false;
				exturn = normal;
				Human.skill.need_jink = false;
				Human.skill.defense_analeptic_kill = false;
				// animator go
				Human.animator_jink = true;
				Human.animator_jink_counter = 0;
				animator_running = true;
				// change button unable
				button_ok.enable_diabled_button();
				button_cancel.enable_diabled_button();
				button_discard.enable_diabled_button();
				// show message box
				Insert_Message(L"人类玩家 出 闪 抵抗！");
				return 0;
			}
		}
		if (button_cancel.is_down) {
			// result
			if (Human.skill.defense_analeptic_kill) Human.HP -= 2;
			else if (Human.skill.need_jink) Human.HP--;

			// show message
			Insert_Message(L"人类玩家 HP 减少了！");

			// judge human is dying?
			Human_Round_enable_dying_state();
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
			if(Human.HP>0)exturn = normal;
			Human.skill.need_jink = false;
			Human.skill.defense_analeptic_kill = false;
			// animator go
			Human.animator_damage = true;
			Human.animator_damage_counter = 0;
			animator_running = true;
			// change button unable
			button_ok.enable_diabled_button();
			button_cancel.enable_diabled_button();
			button_discard.enable_diabled_button();
			return 0;
		}
		return 0;
	}

	if (Human.skill.receive_peach==true) {
		if (Human.HP < Human.limited_HP) Human.HP++;
		Human.skill.receive_peach = false;
		if (Human.HP <= 0) {
			switch (exturn_backup)
			{
			case human:
				Human.skill.begging_peach = true;
				break;
			case machine_0:
				Machine[0].skill.begging_peach = true;
				break;
			case machine_1:
				Machine[1].skill.begging_peach = true;
				break;
			case machine_2:
				Machine[2].skill.begging_peach = true;
				break;
			case machine_3:
				Machine[3].skill.begging_peach = true;
				break;
			default:
				break;
			}
			exturn = exturn_backup;
			exturn_backup = -1;
		}
		else {
			exturn = normal;
			exturn_backup = -1; 
			Machine[0].skill.begging_peach = false;
			Machine[1].skill.begging_peach = false;
			Machine[2].skill.begging_peach = false;
			Machine[3].skill.begging_peach = false;
			peach_begger = -1;    // default one is -1 in case unknown error
			Human.self_save = false;
			Human.is_dying = false;
		}
	}
	
	if (Human.skill.begging_peach) {
		if (button_cancel.is_disabled && button_ok.is_disabled && button_discard.is_disabled)
			button_cancel.enable_normal_button();
		dying_loop = true;
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
				// result
				// figure out who sent begging peach signal then give it
				switch (peach_begger)
				{
				case human:
					Human.skill.receive_peach = true;
					break;
				case machine_0:
					Machine[0].skill.receive_peach = true;
					Insert_Message(L"人类玩家 给 电脑-1 出了一个桃");
					break;
				case machine_1:
					Machine[1].skill.receive_peach = true;
					Insert_Message(L"人类玩家 给 电脑-2 出了一个桃");
					break;
				case machine_2:
					Machine[2].skill.receive_peach = true;
					Insert_Message(L"人类玩家 给 电脑-3 出了一个桃");
					break;
				case machine_3:
					Machine[3].skill.receive_peach = true;
					Insert_Message(L"人类玩家 给 电脑-4 出了一个桃");
					break;
				default:
					break;
				}
				// round change
				exturn_backup = exturn;
				exturn = peach_begger;
				// pile card change
				Human.cards.Delete_Card_Selected();
				discard_pile.Insert_Card(peach, 1);
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
			// result
			/** where exist more player, it turn to next player */
			//if (exturn == machine_3) exturn = human;  // meaning going to a loop
			if (exturn == machine_number+1) exturn = human;  // meaning going to a loop
			else exturn++;
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
			Insert_Message(L"人类玩家 拒绝出桃");
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
				// find node that is chose card
				Single_Card* ptr = Human.cards.Pile_Card_Total->next;
				for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {
					if (ptr->mouse_select_card) break;
					ptr = ptr->next;
				}
				// result
				int which_animator = ptr->card_info.single_card_number;
				if (which_animator == peach || which_animator == analeptic) {
					out_put(*ptr);
					Human.cards.Delete_Card_Selected();
					discard_pile.Insert_Card(peach, 1);
					Human.skill.receive_peach = true;
					exturn_backup = exturn;
				}
				// initialize data
				Human.select_card = false;
				Human.selecet_card_amount = 0;
				// animator go
				if (which_animator == peach) {
					Human.animator_peach = true;
					Human.animator_peach_counter = 0;
					animator_running = true;
					Insert_Message(L"人类玩家 出 桃 自救");
				}
				else if (which_animator == analeptic) {
					Human.animator_analeptic = true;
					Human.animator_analeptic_counter = 0;
					animator_running = true;
					Insert_Message(L"人类玩家 出 酒 自救");
				}
				// change button unable
				button_ok.enable_diabled_button();
				button_cancel.enable_diabled_button();
				button_discard.enable_diabled_button();
				return 0;
			}
		}
		if (button_cancel.is_down) {
			// result
			if (exturn == machine_number+1) exturn = human;  // meaning going to a loop
			else exturn++;
			Human.is_dying = true;
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
			// show message box
			Insert_Message(L"人类玩家 自救结束");
			return 0;
		}
	}
	return 1;
}
void Game::Human_Round() {
	Vector2i mouse_select_vector=Input();;  // in general there only exist one input function  * wtf! that is matter most
	//
	Human_Round_Initialize();
	if(Human_Round_Skill_Judgment(mouse_select_vector)==0) return;

	// Human play card
	if (Human.HP <= 0) Human.self_save = true;
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
						cout << "choseen:::" << number << endl;
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
							//  animator running
							Human.animator_kill = true;
							Human.animator_kill_counter = 0;
							animator_running = true;
							// result
							Machine[number].skill.defense_analeptic_kill = true;
							switch (number)
							{
							case 0:
								exturn = machine_0;
								Insert_Message(L"人类玩家 对 电脑-1 施展 酒杀");
								break;
							case 1:
								exturn = machine_1;
								Insert_Message(L"人类玩家 对 电脑-2 施展 酒杀");
								break;
							case 2:
								exturn = machine_2;
								Insert_Message(L"人类玩家 对 电脑-3 施展 酒杀");
								break;
							case 3:
								exturn = machine_3;
								Insert_Message(L"人类玩家 对 电脑-4 施展 酒杀");
								break;
							}
							Human.kill_times++;
							Human.cards.Delete_Card_Selected();
							discard_pile.Insert_Card(kill, 1);

							cout << "exturn is :::" << exturn << endl;
						}
						else if (ptr->card_info.single_card_number == kill)
						{
							cout << "__killllit:::" << number << endl;
							//  animator running
							Human.animator_kill = true;
							Human.animator_kill_counter = 0;
							animator_running = true;
							// result
							Machine[number].skill.need_jink = true;
							switch (number)
							{
							case 0:
								exturn = machine_0;
								Insert_Message(L"人类玩家 对 电脑-1 施展 杀");
								break;
							case 1:
								exturn = machine_1;
								Insert_Message(L"人类玩家 对 电脑-2 施展 杀");
								break;
							case 2:
								exturn = machine_2;
								Insert_Message(L"人类玩家 对 电脑-3 施展 杀");
								break;
							case 3:
								exturn = machine_3;
								Insert_Message(L"人类玩家 对 电脑-4 施展 杀");
								break;
							default:
								break;
							}
							Human.kill_times++;
							Human.cards.Delete_Card_Selected();
							discard_pile.Insert_Card(kill, 1);

							cout << "exturn is :::" << exturn << endl;
						}
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
						Human.animator_peach = true;
						Human.animator_peach_counter = 0;
						animator_running = true;
						if (Human.HP < Human.limited_HP) Human.HP++;
						discard_pile.Insert_Card(peach, 1);
						Insert_Message(L"人类玩家 施展 桃");
						//Human.skill.need_peach=true;
					}
					else if (ptr->card_info.single_card_number == analeptic) { // when human have not die,this kill can doubled kill power
						Human.kill_power++;
						Human.drank_analeptic = true;
						Human.animator_analeptic = true;
						Human.animator_analeptic_counter = 0;
						animator_running = true;
						discard_pile.Insert_Card(analeptic, 1);
						Insert_Message(L"人类玩家 施展 酒");
					}
					else if (ptr->card_info.single_card_number == amazing_grace) { // get anyone a card
						// round turn
						exturn = human;
						round_loop_starter = human;
						amazing_grace_loop = true;
						// sent skill signal 
						Human.skill.amazing_grace_state = true;
						for (int i = 0; i < machine_number; i++)
							Machine[i].skill.amazing_grace_state = true;
						// piles changes
						discard_pile.Insert_Card(amazing_grace, 1);
						Insert_Message(L"人类玩家 施展 五谷丰登");
						// insert some cards according to current living player
						for (int i = 0; i < machine_number+1; i++) {
							temp_pile.Insert_Card(piles.Pile_Card_Total->next->card_info.single_card_number, piles.Pile_Card_Total->next->card_info.suit);
							piles.Delete_Card(piles.Pile_Card_Total->next->card_info.single_card_number);
						}
						// set each card position (initialize)
						Single_Card* ptr = temp_pile.Pile_Card_Total->next;
						for (int i = 0; i < temp_pile.Pile_Card_Amount; i++) {  // each card:  width 93 || height 130
							if (!ptr->file_loaded) {
								stringstream ss;
								ss << "image/skill&equip_card/small_card/" << ptr->card_info.single_card_number << ".jpg";
								Load_Image(ptr->texture_card, ptr->sprite_card, ss.str(), 0, 0, 1, 1);
								ptr->file_loaded = true;
							}
							ptr->point_one.x = 270 + i * 100;
							ptr->point_one.y = 450;
							ptr->point_two.x = ptr->point_one.x + 93;
							ptr->point_two.y = ptr->point_one.y + 130;
							ptr->mouse_select_card = false;
							ptr = ptr->next;
						}
						button_discard.enable_diabled_button();
						button_cancel.enable_diabled_button();
						button_ok.enable_diabled_button();
					}
					
					Machine[0].being_choose = false;
					Machine[1].being_choose = false;
					Machine[2].being_choose = false;
					Machine[3].being_choose = false;
					Human.chosen_number = 0;
					Human.cards.Delete_Card_Selected();
					Human.select_card = false;
					// then change button state
					button_ok.enable_diabled_button();
					button_cancel.enable_diabled_button();
					button_discard.enable_normal_button();

				}
			}
			if (mouse_select_vector.x > 807 && mouse_select_vector.x < (807 + 61) && mouse_select_vector.y > 694 && mouse_select_vector.y < (694 + 73)) {  // when it go to cancel ,change all anyway
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
			Human.round_play_phase = false;
			Human.round_discard_phase = true;
		}
	}
	// Human discard
	if (Human.round_discard_phase) {

		// there exist tow kind of situation -- original initialize and no hover & no down

		if (Human.cards.Pile_Card_Amount <= Human.HP) {   // no need to discard
			button_ok.enable_diabled_button();
			button_cancel.enable_diabled_button();
			button_discard.enable_diabled_button();
			Human.round_discard_phase = false;
			new_round = true;
			if (turn == machine_number+1) turn = human;  // meaning going to a loop
			else turn++;
			Insert_Message(L"————人类玩家-----回合结束————");
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
			for (int i = 0; i < Human.selecet_card_amount; i++) {
				int temp_delete_number;
				// find that card
				LinkList ptr = Human.cards.Pile_Card_Total;
				while (ptr->next) {
					if (ptr->next->mouse_select_card == true) {
						temp_delete_number = ptr->next->card_info.single_card_number;
						break;
					}
					ptr = ptr->next;
				}

				Human.cards.Delete_Card_Selected();
				discard_pile.Insert_Card(temp_delete_number, 1);
			}
			Human.selecet_card_amount = 0;
			button_ok.enable_diabled_button();
			Human.round_discard_phase = false;
			new_round = true;
			if (turn == machine_number+1) turn = human;  // meaning going to a loop
			else turn++;
			Insert_Message(L"————人类玩家-----回合结束————");
		}
	}

	// button unable when animator start & go
	if (animator_running) {
		button_ok.enable_diabled_button();
		button_cancel.enable_diabled_button();
		button_discard.enable_diabled_button();
	}
}