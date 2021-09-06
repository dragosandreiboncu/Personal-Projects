package champions;

import abilities.FirstSpell;
import abilities.SecondSpell;

public abstract class Champion {
	public String name;
	public int xCoordinate;
	public int yCoordinate;
	protected int hp;
	protected int hpInitial;
	protected int xp;
	protected boolean dead;
	protected int level;
	protected FirstSpell firstSpell;
	protected SecondSpell secondSpell;
	protected boolean incapacitated;
	protected float damageGiven;
	protected int effectRounds;
	protected float damagePerRound;
	protected int effectDamageRounds;

	/**
	 *
	 * @return effectDamageRounds
	 */
	public int getEffectDamageRounds() {
		return effectDamageRounds;
	}
	/**
	 *
	 * @param effectDamageRounds
	 */
	public void setEffectDamageRounds(final int effectDamageRounds) {
		this.effectDamageRounds = effectDamageRounds;
	}
	/**
	 *
	 * @return damagePerRound
	 */
	public float getDamagePerRound() {
		return damagePerRound;
	}
	/**
	 *
	 * @param damagePerRound
	 */
	public void setDamagePerRound(final float damagePerRound) {
		this.damagePerRound = damagePerRound;
	}
	/**
	 *
	 * @return firstSpell
	 */
	public FirstSpell getFirstSpell() {
		return firstSpell;
	}
	/**
	 *
	 * @param firstSpell
	 */
	public void setFirstSpell(final FirstSpell firstSpell) {
		this.firstSpell = firstSpell;
	}
	/**
	 *
	 * @return secondSpell
	 */
	public SecondSpell getSecondSpell() {
		return secondSpell;
	}
	/**
	 *
	 * @param secondSpell
	 */
	public void setSecondSpell(final SecondSpell secondSpell) {
		this.secondSpell = secondSpell;
	}
	/**
	 *
	 * @return effectRounds
	 */
	public int getEffectRounds() {
		return effectRounds;
	}
	/**
	 *
	 * @param effectRounds
	 */
	public void setEffectRounds(final int effectRounds) {
		this.effectRounds = effectRounds;
	}
	/**
	 *
	 * @return hpInitial
	 */
	public int getHpInitial() {
		return hpInitial;
	}
	/**
	 *
	 * @param hpInitial
	 */
	public void setHpInitial(final int hpInitial) {
		this.hpInitial = hpInitial;
	}
	/**
	 *
	 * @return damageGiven
	 */
	public float getDamageGiven() {
		return damageGiven;
	}
	/**
	 *
	 * @param damageGiven
	 */
	public void setDamageGiven(final float damageGiven) {
		this.damageGiven = damageGiven;
	}
	/**
	 *
	 * @return incapacitated
	 */
	public boolean isIncapacitated() {
		return incapacitated;
	}
	/**
	 *
	 * @param incapacitated
	 */
	public void setIncapacitated(final boolean incapacitated) {
		this.incapacitated = incapacitated;
	}
	/**
	 *
	 * @param dead
	 */
	public void setDead(final boolean dead) {
		this.dead = dead;
	}
	/**
	 *
	 * @param level
	 */
	public void setLevel(final int level) {
		this.level = level;
	}
	/**
	 *
	 * @return level
	 */
	public int getLevel() {
		return level;
	}
	/**
	 *
	 * @return dead
	 */
	public boolean isDead() {
		return dead;
	}
	/**
	 *
	 * @return hp
	 */
	public int getHP() {
		return hp;
	}
	/**
	 *
	 * @param hp
	 */
	public void setHP(final int hp) {
		this.hp = hp;
	}
	/**
	 *
	 * @return xp
	 */
	public int getXP() {
		return xp;
	}
	/**
	 *
	 * @param xp
	 */
	public void setXP(final int xp) {
		this.xp = xp;
	}
	/**
	 *
	 * @return name
	 */
	public String getName() {
		return name;
	}
	/**
	 *
	 * @return xCoordinate
	 */
	public int getXCoordinate() {
		return xCoordinate;
	}
	/**
	 *
	 * @return  yCoordinate
	 */
	public int getYCoordinate() {
		return yCoordinate;
	}
}
