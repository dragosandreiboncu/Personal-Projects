package common;

public final class Constants {

	private Constants() {
        // just to trick checkstyle
    }

	public static final String KNIGHT = "K";
	public static final String WIZARD = "W";
	public static final String PYROMANCER = "P";
	public static final String ROGUE = "R";

	public static final String LAND = "L";
	public static final String VOLCANIC = "V";
	public static final String DESERT = "D";
	public static final String WOODS = "W";

	public static final int TWO_HUNDRED = 200;
	public static final int FORTY = 40;

	public static final int INITIAL_XP = 0;

	public static final int HP_KNIGHT = 900;
	public static final int HP_PYROMANCER = 500;
	public static final int HP_WIZARD = 400;
	public static final int HP_ROGUE = 600;

	public static final String UP = "U";
	public static final String DOWN = "D";
	public static final String RIGHT = "R";
	public static final String LEFT = "L";
	public static final String STAY = "_";

	public static final int LEVEL_UP = 250;
	public static final int NEXT_LEVEL = 50;
	public static final int LEVEL_HP_K = 80;
	public static final int LEVEL_HP_R = 40;
	public static final int LEVEL_HP_P = 50;
	public static final int LEVEL_HP_W = 30;

	public static final int ROUND_INCAPACITATED = 1;
	public static final int DAMAGE_EXECUTE = 200;
	public static final int EXECUTE_LEVEL = 30;
	public static final float PERCENT_EXECUTE_KILL = 0.2f;
	public static final float PERCENT_EXECUTE_KILL_LEVEL = 0.01f;
	public static final float PERCENT_EXECUTE_MAX = 0.4f;
	public static final float EXECUTE_ROGUE = 0.15f;
	public static final float EXECUTE_KNIGHT = 0f;
	public static final float EXECUTE_PYROMANCER = 0.1f;
	public static final float EXECUTE_WIZARD = -0.2f;

	public static final int DAMAGE_SLAM = 100;
	public static final int SLAM_LEVEL = 40;
	public static final float SLAM_ROGUE = -0.2f;
	public static final float SLAM_KNIGHT = 0.2f;
	public static final float SLAM_PYROMANCER = -0.1f;
	public static final float SLAM_WIZARD = 0.05f;

	public static final float KNIGHT_TERRAIN = 1.15f;

	public static final int DAMAGE_FIREBLAST = 350;
	public static final int FIREBLAST_LEVEL = 50;
	public static final float FIREBLAST_ROGUE = -0.2f;
	public static final float FIREBLAST_KNIGHT = 0.2f;
	public static final float FIREBLAST_PYROMANCER = -0.1f;
	public static final float FIREBLAST_WIZARD = 0.05f;

	public static final float PERCENT_ROGUE = 0.3f;
	public static final int DAMAGE_IGNITE = 150;
	public static final int DAMAGE_ROUND = 50;
	public static final int IGNITE_LEVEL = 20;
	public static final int DAMAGE_ROUND_LEVEL = 30;
	public static final float IGNITE_ROGUE = -0.2f;
	public static final float IGNITE_KNIGHT = 0.2f;
	public static final float IGNITE_PYROMANCER = -0.1f;
	public static final float IGNITE_WIZARD = 0.05f;

	public static final float PYROMANCER_TERRAIN = 1.25f;

	public static final int TIME_FOR_CRITICAL = 3;
	public static final int DAMAGE_BACKSTAB = 200;
	public static final int BACKSTAB_LEVEL = 20;
	public static final float CRITICAL = 1.5f;
	public static final float BACKSTAB_ROGUE = 0.2f;
	public static final float BACKSTAB_KNIGHT = -0.1f;
	public static final float BACKSTAB_PYROMANCER = 0.25f;
	public static final float BACKSTAB_WIZARD = 0.25f;

	public static final int DAMAGE_PARALYSIS = 40;
	public static final int PARALYSIS_LEVEL = 10;
	public static final float PARALYSIS_ROGUE = -0.1f;
	public static final float PARALYSIS_KNIGHT = -0.2f;
	public static final float PARALYSIS_PYROMANCER = 0.2f;
	public static final float PARALYSIS_WIZARD = 0.25f;

	public static final int OVERTIME_R_NORMAL = 3;
	public static final int OVERTIME_R_WOODS = 6;
	public static final float ROGUE_TERRAIN = 1.15f;

	public static final float DAMAGE_DRAIN = 0.2f;
	public static final float DRAIN_LEVEL = 0.05f;
	public static final float DRAIN_ROGUE = -0.2f;
	public static final float DRAIN_KNIGHT = 0.2f;
	public static final float DRAIN_PYROMANCER = -0.1f;
	public static final float DRAIN_WIZARD = 0.05f;

	public static final float DAMAGE_DEFLECT = 0.35f;
	public static final float DEFLECT_LEVEL = 0.02f;
	public static final float DEFLECT_ROGUE = 0.2f;
	public static final float DEFLECT_KNIGHT = 0.4f;
	public static final float DEFLECT_PYROMANCER = 1.3f;

	public static final float WIZARD_TERRAIN = 1.1f;
}
