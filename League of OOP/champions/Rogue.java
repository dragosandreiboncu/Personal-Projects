package champions;

import common.Constants;
import abilities.Backstab;
import abilities.Paralysis;

public class Rogue extends Champion {
	public Rogue() {
		//setarea informatiilor despre jucatori ( hp, abilitati)
		this.xp = Constants.INITIAL_XP;
		this.hp = Constants.HP_ROGUE;
		this.hpInitial = Constants.HP_ROGUE;
		this.dead = false;
		this.level = 0;
		this.incapacitated = false;
		this.firstSpell = new Backstab();
		this.secondSpell = new Paralysis();
		this.incapacitated = false;
		this.damageGiven = 0;
		this.effectRounds = 0;
	}
}
