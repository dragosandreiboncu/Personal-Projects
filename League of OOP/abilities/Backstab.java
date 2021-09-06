package abilities;

import champions.Champion;
import common.Constants;

public final class Backstab extends FirstSpell {
	// folosit pentru a stii cand aplica critical
	private int counter = 0;
	public void firstSpell(final Champion attacker, final Champion enemy,
							final String terrain) {

		attacker.setDamageGiven(Constants.DAMAGE_BACKSTAB + attacker.getLevel()
								* Constants.BACKSTAB_LEVEL);
		//modificator de teren si critical
		if (counter % Constants.TIME_FOR_CRITICAL == 0 && terrain.equals(Constants.WOODS)) {
			attacker.setDamageGiven(attacker.getDamageGiven() * Constants.CRITICAL);
		}
		// modificator de rasa
		if (terrain.equals(Constants.WOODS)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
									* Constants.ROGUE_TERRAIN);
		}

		if (enemy.getName().equals(Constants.ROGUE)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
				+ attacker.getDamageGiven() * Constants.BACKSTAB_ROGUE);
		}

		if (enemy.getName().equals(Constants.KNIGHT)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
				+ attacker.getDamageGiven() * Constants.BACKSTAB_KNIGHT);
		}

		if (enemy.getName().equals(Constants.PYROMANCER)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
				+ attacker.getDamageGiven() * Constants.BACKSTAB_PYROMANCER);
		}

		if (enemy.getName().equals(Constants.WIZARD)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
				+ attacker.getDamageGiven() * Constants.BACKSTAB_WIZARD);
		}

		attacker.setDamageGiven(Math.round(attacker.getDamageGiven()));
		counter++;
	}
}
