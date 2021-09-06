package champions;

import common.Constants;
import abilities.Drain;
import abilities.Deflect;

public class Wizard extends Champion {
	public Wizard() {
		//setarea informatiilor despre jucatori ( hp, abilitati)
		this.xp = Constants.INITIAL_XP;
		this.hp = Constants.HP_WIZARD;
		this.hpInitial = Constants.HP_WIZARD;
		this.dead = false;
		this.level = 0;
		this.incapacitated = false;
		this.firstSpell = new Drain();
		this.secondSpell = new Deflect();
		this.incapacitated = false;
		this.damageGiven = 0;
		this.effectRounds = 0;
	}
}
