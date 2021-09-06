package abilities;

import champions.Champion;
import common.Constants;

public final class Drain extends FirstSpell {
	public void firstSpell(final Champion attacker, final Champion enemy,
							final String terrain) {

		attacker.setDamageGiven(Constants.DAMAGE_DRAIN
				+ attacker.getLevel() * Constants.DRAIN_LEVEL);

		if (terrain.equals(Constants.DESERT)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					* Constants.WIZARD_TERRAIN);
		}

		if (enemy.getName().equals(Constants.ROGUE)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ attacker.getDamageGiven() * Constants.DRAIN_ROGUE);
		}

		if (enemy.getName().equals(Constants.KNIGHT)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ attacker.getDamageGiven() * Constants.DRAIN_KNIGHT);
		}

		if (enemy.getName().equals(Constants.PYROMANCER)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ attacker.getDamageGiven() * Constants.DRAIN_PYROMANCER);
		}

		if (enemy.getName().equals(Constants.WIZARD)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ attacker.getDamageGiven() * Constants.DRAIN_WIZARD);
		}

		attacker.setDamageGiven(attacker.getDamageGiven() * Math.min(Constants.PERCENT_ROGUE
				* enemy.getHpInitial(), enemy.getHP()));
		attacker.setDamageGiven(Math.round(attacker.getDamageGiven()));
	}
}
