package abilities;

import champions.Champion;
import common.Constants;

public final class Paralysis extends SecondSpell {
	public void secondSpell(final Champion attacker, final Champion enemy,
			final String terrain) {

		attacker.setDamageGiven(Constants.DAMAGE_PARALYSIS
				+ attacker.getLevel() * Constants.PARALYSIS_LEVEL);
		// setarea damage-ului overtime
		enemy.setDamagePerRound(Constants.DAMAGE_PARALYSIS
				+ Constants.PARALYSIS_LEVEL * attacker.getLevel());
		// modificator de teren
		if (terrain.equals(Constants.WOODS)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					* Constants.ROGUE_TERRAIN);
			enemy.setDamagePerRound(enemy.getDamagePerRound()
					* Constants.ROGUE_TERRAIN);
			enemy.setEffectRounds(Constants.OVERTIME_R_WOODS);
		} else {
			enemy.setEffectRounds(Constants.OVERTIME_R_NORMAL);

		}
		// inamicul nu poate sa se mai miste pe harta
		enemy.setIncapacitated(true);
		// modificator de rasa
		if (enemy.getName().equals(Constants.ROGUE)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ attacker.getDamageGiven() * Constants.PARALYSIS_ROGUE);
			enemy.setDamagePerRound(enemy.getDamagePerRound()
					+ enemy.getDamagePerRound() * Constants.PARALYSIS_ROGUE);
		}

		if (enemy.getName().equals(Constants.KNIGHT)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ attacker.getDamageGiven() * Constants.PARALYSIS_KNIGHT);
			enemy.setDamagePerRound(enemy.getDamagePerRound()
					+ enemy.getDamagePerRound() * Constants.PARALYSIS_KNIGHT);
		}

		if (enemy.getName().equals(Constants.PYROMANCER)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ attacker.getDamageGiven()
					* Constants.PARALYSIS_PYROMANCER);
			enemy.setDamagePerRound(enemy.getDamagePerRound()
					+ enemy.getDamagePerRound()
					* Constants.PARALYSIS_PYROMANCER);
		}

		if (enemy.getName().equals(Constants.WIZARD)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ attacker.getDamageGiven() * Constants.PARALYSIS_WIZARD);
			enemy.setDamagePerRound(enemy.getDamagePerRound()
					+ enemy.getDamagePerRound() * Constants.PARALYSIS_WIZARD);
		}
		attacker.setDamageGiven(Math.round(attacker.getDamageGiven()));
		enemy.setDamagePerRound(Math.round(enemy.getDamagePerRound()));
	}
}
