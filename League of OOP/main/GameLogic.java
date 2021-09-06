package main;

import java.util.ArrayList;
import champions.Champion;
import common.Constants;


public final class GameLogic {

	public void move(final ArrayList<Champion> champions, final String[][] moves,
			final String[][] map) {
		// mutarea fiecarui jucator si verificam daca se pot misca
		for (int i = 0; i < moves.length; i++) {
			for (int j = 0; j < champions.size(); j++) {
				if (moves[i][j].equals(Constants.UP)
						&& !champions.get(j).isIncapacitated()) {
					champions.get(j).xCoordinate--;
				}
				if (moves[i][j].equals(Constants.DOWN)
						&& !champions.get(j).isIncapacitated()) {
					champions.get(j).xCoordinate++;
				}
				if (moves[i][j].equals(Constants.RIGHT)
						&& !champions.get(j).isIncapacitated()) {
					champions.get(j).yCoordinate++;
				}
				if (moves[i][j].equals(Constants.LEFT)
						&& !champions.get(j).isIncapacitated()) {
					champions.get(j).yCoordinate--;
				}
				// damage-ul overtime
				if (champions.get(j).getEffectRounds() > 0) {
					champions.get(j).setHP(
							champions.get(j).getHP()
							- (int) champions.get(j).getDamagePerRound());
					champions.get(j).setEffectRounds(
							champions.get(j).getEffectRounds() - 1);
				}
				if (champions.get(j).getEffectRounds() == 0) {
					champions.get(j).setIncapacitated(false);
				}
				if (champions.get(j).getHP() <= 0) {
					champions.get(j).setDead(true);
				}
			}
			for (int j = 0; j < champions.size() - 1; j++) {
				for (int k = j + 1; k < champions.size(); k++) {
					// verificam daca doi jucatori s-au intalnit
					if (champions.get(j).xCoordinate
							== champions.get(k).xCoordinate
							&& champions.get(j).yCoordinate
							== champions.get(k).yCoordinate
							&& !champions.get(j).isDead()
							&& !champions.get(k).isDead()) {
						String terrain = map[champions.get(j).xCoordinate][champions.get(j).yCoordinate];
						fight(champions.get(j), champions.get(k), terrain);
					}
				}
			}
			levelUp(champions);
		}
	}

	public void levelUp(final ArrayList<Champion> champions) {
		// verificam fiecare jucator daca trebuie sa faca level up
		for (int j = 0; j < champions.size(); j++) {
			while (champions.get(j).getXP() >= Constants.LEVEL_UP
					+ Constants.NEXT_LEVEL * champions.get(j).getLevel()) {
				if (champions.get(j).getName().equals(Constants.KNIGHT)) {
					champions.get(j).setHpInitial(champions.get(j).getHpInitial()
							+ Constants.LEVEL_HP_K);
					champions.get(j).setHP(champions.get(j).getHpInitial());
					champions.get(j).setLevel(champions.get(j).getLevel() + 1);
				}
				if (champions.get(j).getName().equals(Constants.PYROMANCER)) {
					champions.get(j).setHpInitial(champions.get(j).getHpInitial()
							+ Constants.LEVEL_HP_P);
					champions.get(j).setHP(champions.get(j).getHpInitial());
					champions.get(j).setLevel(champions.get(j).getLevel() + 1);
				}
				if (champions.get(j).getName().equals(Constants.ROGUE)) {
					champions.get(j).setHpInitial(champions.get(j).getHpInitial()
							+ Constants.LEVEL_HP_R);
					champions.get(j).setHP(champions.get(j).getHpInitial());
					champions.get(j).setLevel(champions.get(j).getLevel() + 1);
				}
				if (champions.get(j).getName().equals(Constants.WIZARD)) {
					champions.get(j).setHpInitial(champions.get(j).getHpInitial()
							+ Constants.LEVEL_HP_W);
					champions.get(j).setHP(champions.get(j).getHpInitial());
					champions.get(j).setLevel(champions.get(j).getLevel() + 1);
				}
			}
		}
	}
	public void fight(final Champion championOne, final Champion championTwo,
			final String terrain) {
		// lupta dintre doi jucatori
		// aplicarea primulei abilitati de la primul jucator
		championOne.getFirstSpell().firstSpell(championOne, championTwo, terrain);
		championTwo.setHP(championTwo.getHP() - (int) championOne.getDamageGiven());
		championOne.setDamageGiven(0);
		// aplicarea abilitatii a doua
		championOne.getSecondSpell().secondSpell(championOne, championTwo, terrain);
		championTwo.setHP(championTwo.getHP() - (int) championOne.getDamageGiven());
		championOne.setDamageGiven(0);
		// pentru al doilea jucator
		championTwo.getFirstSpell().firstSpell(championTwo, championOne, terrain);
		championOne.setHP(championOne.getHP() - (int) championTwo.getDamageGiven());
		championTwo.setDamageGiven(0);

		championTwo.getSecondSpell().secondSpell(championTwo, championOne, terrain);
		championOne.setHP(championOne.getHP() - (int) championTwo.getDamageGiven());
		championTwo.setDamageGiven(0);
		// verificam daca unul dintre ei a murit, iar celalalt primeste xp
		if (championOne.getHP() <= 0) {
			championOne.setDead(true);
			championTwo.setXP(championTwo.getXP() + Math.max(0, Constants.TWO_HUNDRED
					- (championTwo.getLevel() - championOne.getLevel())
					* Constants.FORTY));
		}
		if (championTwo.getHP() <= 0) {
			championTwo.setDead(true);
			championOne.setXP(championOne.getXP() + Math.max(0, Constants.TWO_HUNDRED
					- (championOne.getLevel() - championTwo.getLevel())
					* Constants.FORTY));
		}
	}
}
