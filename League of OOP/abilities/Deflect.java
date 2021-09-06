package abilities;

import champions.Champion;
import common.Constants;

public final class Deflect extends SecondSpell {
	public void secondSpell(final Champion attacker, final Champion enemy,
							final String terrain) {
		// modificator de rasa
		// modifcat daca se afla pe terenul favorabil pe inmaci
		if (enemy.getName().equals(Constants.ROGUE)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ Constants.DAMAGE_BACKSTAB);

			if (terrain.equals(Constants.WOODS)) {
				attacker.setDamageGiven(attacker.getDamageGiven()
						* Constants.CRITICAL);
			}
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ Constants.DAMAGE_PARALYSIS);
			attacker.setDamageGiven(attacker.getDamageGiven()
					* Constants.DAMAGE_DEFLECT);

			if (terrain.equals(Constants.WOODS)) {
				attacker.setDamageGiven(attacker.getDamageGiven()
						* Constants.ROGUE_TERRAIN);
			}
			attacker.setDamageGiven(Math.round(attacker.getDamageGiven()));
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ attacker.getDamageGiven() * Constants.DEFLECT_ROGUE);
		}

		if (enemy.getName().equals(Constants.KNIGHT)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ Constants.DAMAGE_EXECUTE);
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ Constants.DAMAGE_SLAM);
			attacker.setDamageGiven(attacker.getDamageGiven()
					* Constants.DAMAGE_DEFLECT);

			if (terrain.equals(Constants.LAND)) {
				attacker.setDamageGiven(attacker.getDamageGiven()
						* Constants.KNIGHT_TERRAIN);
			}
			attacker.setDamageGiven(Math.round(attacker.getDamageGiven()));
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ attacker.getDamageGiven() * Constants.DEFLECT_KNIGHT);
		}

		if (enemy.getName().equals(Constants.PYROMANCER)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ Constants.DAMAGE_FIREBLAST);
			attacker.setDamageGiven(attacker.getDamageGiven()
					+ Constants.DAMAGE_IGNITE);
			attacker.setDamageGiven(attacker.getDamageGiven()
					* Constants.DAMAGE_DEFLECT);

			if (terrain.equals(Constants.VOLCANIC)) {
				attacker.setDamageGiven(attacker.getDamageGiven()
						* Constants.PYROMANCER_TERRAIN);
			}
			attacker.setDamageGiven(Math.round(attacker.getDamageGiven()));
			attacker.setDamageGiven(attacker.getDamageGiven()
					* Constants.DEFLECT_PYROMANCER);
		}
		// daca inamicul e Wizard damage-ul e setat 0
		if (enemy.getName().equals(Constants.WIZARD)) {
			attacker.setDamageGiven(0);
		}
		// modificator de teren
		if (terrain.equals(Constants.DESERT)) {
			attacker.setDamageGiven(attacker.getDamageGiven()
					* Constants.WIZARD_TERRAIN);
		}
		attacker.setDamageGiven(Math.round(attacker.getDamageGiven()));
	}
}
