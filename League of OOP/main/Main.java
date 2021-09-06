package main;

public final class Main {

	private Main() {
        // just to trick checkstyle
    }

	public static void main(final String[] args) {

		GameInputAndOutput game = new GameInputAndOutput();
	 	GameLogic logic = new GameLogic();

		game.readInput(args[0], args[1]);

		logic.move(game.champions, game.moves, game.mapTypes);

		game.writeOut(args[0], args[1]);
	}
}
