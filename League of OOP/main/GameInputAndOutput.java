package main;

import java.util.ArrayList;
import common.Constants;
import champions.Champion;
import champions.Knight;
import champions.Pyromancer;
import champions.Rogue;
import champions.Wizard;
import fileio.FileSystem;

public final class GameInputAndOutput {

	private int mapLines;
	private int mapColumns;
	protected String[][] mapTypes;
	private int nrChampions;
	protected ArrayList<Champion> champions = new ArrayList<>();
	private int nrRounds;
	protected String[][] moves;

    public void readInput(final String input, final String output) {

    	try {
    		FileSystem file = new FileSystem(input, output);

    		// citim din fisier
    		mapLines = file.nextInt();
    		mapColumns = file.nextInt();
    		mapTypes = new String[mapLines][mapColumns];

    		// mapa
    		for (int i = 0; i < mapLines; i++) {
    			mapTypes[i] = file.nextWord().split("");
    		}

    		nrChampions = file.nextInt();
    		// jucatorii si setarea coordonatelor
    		for (int i = 0; i < nrChampions; i++) {
    			String championType = file.nextWord();

    			if (championType.equals(Constants.KNIGHT)) {
    				Champion auxiliar = new Knight();
    				auxiliar.name = Constants.KNIGHT;
    				auxiliar.xCoordinate = file.nextInt();
    				auxiliar.yCoordinate = file.nextInt();
    				champions.add(auxiliar);
    			}

    			if (championType.equals(Constants.PYROMANCER)) {
    				Champion auxiliar = new Pyromancer();
    				auxiliar.name = Constants.PYROMANCER;
    				auxiliar.xCoordinate = file.nextInt();
    				auxiliar.yCoordinate = file.nextInt();
    				champions.add(auxiliar);
    			}

    			if (championType.equals(Constants.ROGUE)) {
    				Champion auxiliar = new Rogue();
    				auxiliar.name = Constants.ROGUE;
    				auxiliar.xCoordinate = file.nextInt();
    				auxiliar.yCoordinate = file.nextInt();
    				champions.add(auxiliar);
    			}

    			if (championType.equals(Constants.WIZARD)) {
    				Champion auxiliar = new Wizard();
    				auxiliar.name = Constants.WIZARD;
    				auxiliar.xCoordinate = file.nextInt();
    				auxiliar.yCoordinate = file.nextInt();
    				champions.add(auxiliar);
    			}
    		}
    		//rundele
    		nrRounds = file.nextInt();
    		// miscarile fiecarui jucator
    		moves = new String[nrRounds][nrChampions];
    		for (int i = 0; i < nrRounds; i++) {
    			moves[i] = file.nextWord().split("");
    		}

    		file.close();

    	} catch (Exception e1) {
    		e1.printStackTrace();
    	}
    }

    public void writeOut(final String input, final String output) {
    	// scrierea in fisier
    	try {
    		FileSystem file = new FileSystem(input, output);

    		for (int i = 0; i < nrChampions; i++) {
    			if (champions.get(i).isDead()) {
    				file.writeWord(champions.get(i).name);
    				file.writeCharacter(' ');
    				file.writeWord("dead");
    				file.writeNewLine();
    			}
    			if (!champions.get(i).isDead()) {
    				file.writeWord(champions.get(i).name);
    				file.writeCharacter(' ');
    				file.writeInt(champions.get(i).getLevel());
    				file.writeCharacter(' ');
    				file.writeInt(champions.get(i).getXP());
    				file.writeCharacter(' ');
    				file.writeInt(champions.get(i).getHP());
    				file.writeCharacter(' ');
    				file.writeInt(champions.get(i).getXCoordinate());
    				file.writeCharacter(' ');
    				file.writeInt(champions.get(i).getYCoordinate());
    				file.writeNewLine();
    			}
    		}

    		file.close();

    	} catch (Exception e1) {
    		e1.printStackTrace();
    	}
    }
}
