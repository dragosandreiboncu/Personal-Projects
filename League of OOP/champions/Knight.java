package champions;

import abilities.Execute;
import abilities.Slam;
import common.Constants;

public class Knight extends Champion {
	public Knight() {
		//setarea informatiilor despre jucatori ( hp, abilitati)
		this.xp = Constants.INITIAL_XP;
		this.hp = Constants.HP_KNIGHT;
		this.hpInitial = Constants.HP_KNIGHT;
		this.dead = false;
		this.level = 0;
		this.firstSpell = new Execute();
		this.secondSpell = new Slam();
		this.incapacitated = false;
		this.damageGiven = 0;
		this.effectRounds = 0;
	}
}
