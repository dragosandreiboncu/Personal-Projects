package abilities;

import champions.Champion;
import common.Constants;

public final class Fireblast extends FirstSpell {
	public void firstSpell(final Champion attacker, final Champion enemy,
			final String terrain) {

		attacker.setDamageGiven(Constants.DAMAGE_FIREBLAST
				+ attacker.getLevel() * Constants.FIREBLAST_LEVEL);
		//modificator de teren
		if (terrain.equals(Constants.VOLCANIC)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					* Constants.PYROMANCER_TERRAIN);
		}
		// modificator de rasa
		if (enemy.getName().equals(Constants.ROGUE)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ attacker.getDamageGiven() * Constants.FIREBLAST_ROGUE);
		}

		if (enemy.getName().equals(Constants.KNIGHT)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ attacker.getDamageGiven() * Constants.FIREBLAST_KNIGHT);
		}

		if (enemy.getName().equals(Constants.PYROMANCER)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ attacker.getDamageGiven()
					* Constants.FIREBLAST_PYROMANCER);
		}

		if (enemy.getName().equals(Constants.WIZARD)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ attacker.getDamageGiven() * Constants.FIREBLAST_WIZARD);
		}

		attacker.setDamageGiven(Math.round(attacker.getDamageGiven()));
	}
}
