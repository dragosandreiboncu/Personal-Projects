package champions;

import abilities.Fireblast;
import abilities.Ignite;
import common.Constants;

public class Pyromancer extends Champion {
	public Pyromancer() {
		//setarea informatiilor despre jucatori ( hp, abilitati)
		this.xp = Constants.INITIAL_XP;
		this.hp = Constants.HP_PYROMANCER;
		this.hpInitial = Constants.HP_PYROMANCER;
		this.dead = false;
		this.level = 0;
		this.incapacitated = false;
		this.firstSpell = new Fireblast();
		this.secondSpell = new Ignite();
		this.incapacitated = false;
		this.damageGiven = 0;
		this.effectRounds = 0;
	}
}
