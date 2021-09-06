package abilities;

import champions.Champion;
import common.Constants;

public final class Slam extends SecondSpell {
	public void secondSpell(final Champion attacker, final Champion enemy,
			final String terrain) {

		attacker.setDamageGiven(Constants.DAMAGE_SLAM
				+ attacker.getLevel() * Constants.SLAM_LEVEL);
		// modificator de teren
		if (terrain.equals(Constants.LAND)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					* Constants.KNIGHT_TERRAIN);
		}
		// modificator de rasa
		if (enemy.getName().equals(Constants.ROGUE)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ attacker.getDamageGiven() * Constants.SLAM_ROGUE);
		}

		if (enemy.getName().equals(Constants.KNIGHT)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ attacker.getDamageGiven() * Constants.SLAM_KNIGHT);
		}

		if (enemy.getName().equals(Constants.PYROMANCER)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ attacker.getDamageGiven() * Constants.SLAM_PYROMANCER);
		}

		if (enemy.getName().equals(Constants.WIZARD)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ attacker.getDamageGiven() * Constants.SLAM_WIZARD);
		}

		attacker.setDamageGiven(Math.round(attacker.getDamageGiven()));
		// inamicul nu poate sa se mai miste pe harta
		enemy.setIncapacitated(true);
		enemy.setEffectRounds(Constants.ROUND_INCAPACITATED);
	}
}
