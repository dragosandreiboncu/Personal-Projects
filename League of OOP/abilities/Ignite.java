package abilities;

import champions.Champion;
import common.Constants;

public final class Ignite extends SecondSpell {
	public void secondSpell(final Champion attacker, final Champion enemy,
			final String terrain) {

		attacker.setDamageGiven(Constants.DAMAGE_IGNITE
				+ attacker.getLevel() * Constants.IGNITE_LEVEL);
		enemy.setEffectRounds(2);
		// setarea damage-ului overtime
		enemy.setDamagePerRound(Constants.DAMAGE_ROUND
				+ Constants.DAMAGE_ROUND_LEVEL * attacker.getLevel());
		// modificator de teren
		if (terrain.equals(Constants.VOLCANIC)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					* Constants.PYROMANCER_TERRAIN);
			enemy.setDamagePerRound(enemy.getDamagePerRound()
					* Constants.PYROMANCER_TERRAIN);
		}
		// modificator de rasa
		if (enemy.getName().equals(Constants.ROGUE)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ attacker.getDamageGiven() * Constants.IGNITE_ROGUE);
			enemy.setDamagePerRound(enemy.getDamagePerRound()
					+ enemy.getDamagePerRound() * Constants.IGNITE_ROGUE);
		}

		if (enemy.getName().equals(Constants.KNIGHT)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ attacker.getDamageGiven() * Constants.IGNITE_KNIGHT);
			enemy.setDamagePerRound(enemy.getDamagePerRound()
					+ enemy.getDamagePerRound() * Constants.IGNITE_KNIGHT);
		}

		if (enemy.getName().equals(Constants.PYROMANCER)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ attacker.getDamageGiven() * Constants.IGNITE_PYROMANCER);
			enemy.setDamagePerRound(enemy.getDamagePerRound()
					+ enemy.getDamagePerRound() * Constants.IGNITE_PYROMANCER);
		}

		if (enemy.getName().equals(Constants.WIZARD)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ attacker.getDamageGiven() * Constants.IGNITE_WIZARD);
			enemy.setDamagePerRound(enemy.getDamagePerRound()
					+ enemy.getDamagePerRound() * Constants.IGNITE_WIZARD);
		}

		attacker.setDamageGiven(Math.round(attacker.getDamageGiven()));
		enemy.setDamagePerRound(Math.round(enemy.getDamagePerRound()));
	}
}
