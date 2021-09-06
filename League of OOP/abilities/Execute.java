package abilities;

import common.Constants;
import champions.Champion;

public final class Execute extends FirstSpell {
	public void firstSpell(final Champion attacker, final Champion enemy,
							final String terrain) {

		attacker.setDamageGiven(Constants.DAMAGE_EXECUTE + attacker.getLevel()
				* Constants.EXECUTE_LEVEL);
		// verificarea hp-ului daca e sub limita
		if (enemy.getHP() <= enemy.getHpInitial() * Math.min((Constants.PERCENT_EXECUTE_KILL
				+ attacker.getLevel() * Constants.PERCENT_EXECUTE_KILL_LEVEL),
				Constants.PERCENT_EXECUTE_MAX)) {
			enemy.setHP(0);
			enemy.setDead(true);
			return;
		}
		// modificator de teren
		if (terrain.equals(Constants.LAND)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					* Constants.KNIGHT_TERRAIN);
		}
		// modificator de rasa
		if (enemy.getName().equals(Constants.ROGUE)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ attacker.getDamageGiven() * Constants.EXECUTE_ROGUE);
		}

		if (enemy.getName().equals(Constants.KNIGHT)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ attacker.getDamageGiven() * Constants.EXECUTE_KNIGHT);
		}

		if (enemy.getName().equals(Constants.PYROMANCER)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ attacker.getDamageGiven() * Constants.EXECUTE_PYROMANCER);
		}

		if (enemy.getName().equals(Constants.WIZARD)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ attacker.getDamageGiven() * Constants.EXECUTE_WIZARD);
		}

		attacker.setDamageGiven(Math.round(attacker.getDamageGiven()));
	}
}
