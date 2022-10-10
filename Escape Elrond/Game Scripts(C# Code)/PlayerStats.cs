using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayerStats : MonoBehaviour
{
    public int life;
    public int maxHealth = 100;
    public int experience;
    public int coins;
    public int level = 1;

    public HealthBar healthBar;
    public ProgressBar progressBar;
    public Coins playerCoins;
    public GameObject deathMenu;
    public SkillTree st;
    public GameObject tree;
    public bool treeIsUp;
    [SerializeField] private AudioSource gameOverSound;
    [SerializeField] private AudioSource takeDamageSound;
    public Image skillPointsNotUsed;
    public Image duskShield1;
    public Image duskShield2;
    [SerializeField] private AudioSource duskShieldSound;
    [SerializeField] private AudioSource duskShieldDestroyedSound;

    public int attack = 10;
    public int defense = 0;
    private bool gameOver = false;
    private float elapsedTimeDuskShield;
    private float cooldownDuskShield;
    private bool duskShieldActivated;
    private Skills duskShield;

    // Start is called before the first frame update
    void Start()
    {
        duskShieldActivated = false;
        cooldownDuskShield = 20f;
        SetReferences();
        Time.timeScale = 1f;
        //st.points = 0;
        life = maxHealth;
        healthBar.SetMaxHealth(maxHealth);
        experience = 0;
        treeIsUp = false;
    }

    // Update is called once per frame
    void Update()
    {
        if (experience / level >= 100)
        {
            experience = experience - 100 * level;
            level++;
            st.points++;
            st.UpdateTalentPointText();
            attack = attack + 2;
            maxHealth = maxHealth + 20;
            life = maxHealth;
            healthBar.SetMaxHealth(maxHealth);
            healthBar.SetHealth(maxHealth);
        }
   
        playerCoins.SetCoin(coins);
        healthBar.SetHealth(life);
        progressBar.CurrentValue = experience;
        progressBar.lvl = level;
        //experience = progressBar.CurrentValue();

        if (life <= 0)
        {
            if (!gameOver)
            {
                gameOver = true;
                gameOverSound.Play();
                Time.timeScale = 0f;
                deathMenu.SetActive(true);
                //death screen
                st.points = 0;
                healthBar.SetA(false);
                progressBar.SetA(false);
                playerCoins.SetA(false);
                skillPointsNotUsed.enabled = false;
                duskShield1.enabled = false;
                duskShield2.enabled = false;
            }
        }

        /*if (Input.GetKeyDown(KeyCode.P))
        {
            life = life - 500;
        }
        if (Input.GetKeyDown(KeyCode.X))
        {
            experience += 1000;
        }*/
        if (Input.GetKeyDown(KeyCode.N))
        {
            if (treeIsUp == false)
            {
                tree.SetActive(true);
                treeIsUp = true;
            }
            else
            {
                tree.SetActive(false);
                treeIsUp = false;
            }
        }

        if (Input.GetKeyDown(KeyCode.Escape))
        {
            if (treeIsUp)
            {
                tree.SetActive(false);
                treeIsUp = false;
            }
        }
        if (cooldownDuskShield < 20f)
        {
            cooldownDuskShield += Time.deltaTime;
        }
        if (duskShieldActivated)
        {
            elapsedTimeDuskShield += Time.deltaTime;
            if (elapsedTimeDuskShield > 10f)
            {
                duskShieldActivated = false;
                duskShield1.enabled = false;
                duskShield2.enabled = false;
                duskShieldDestroyedSound.Play();
                cooldownDuskShield = 0f;
            }
        }

        if (Input.GetKeyDown(KeyCode.Alpha2) || Input.GetKeyDown(KeyCode.Keypad2))
        {
            if (!duskShieldActivated && cooldownDuskShield >= 20f && duskShield.skillAvailable)
            {
                duskShieldSound.Play();
                elapsedTimeDuskShield = 0f;
                duskShieldActivated = true;
                duskShield1.enabled = true;
                duskShield2.enabled = true;
            }
        }

        if (st.points > 0)
        {
            skillPointsNotUsed.enabled = true;
        } else
        {
            skillPointsNotUsed.enabled = false;
        }
            // level up 100xp -> 2, 200xp -> 3, 300xp -> 4 and so on

    }

    public void TakeDamage(int damage)
    {
        if (duskShieldActivated)
        {
            if (duskShield2.enabled)
            {
                duskShield2.enabled = false;
            }
            else
            {
                duskShield1.enabled = false;
                duskShieldActivated = false;
                cooldownDuskShield = 0f;
            }
            duskShieldDestroyedSound.Play();
        }
        else
        {
            takeDamageSound.Play();
            life -= damage;
            healthBar.SetHealth(life);
        }
    }

    void SetReferences()
    {
        tree = GameObject.Find("Skill_Tree_Canvas(Clone)").transform.GetChild(0).gameObject;
        st = tree.GetComponent<SkillTree>();
        GameObject stree = GameObject.Find("Skill_Tree_Canvas(Clone)").transform.GetChild(0).gameObject;
        GameObject background = stree.transform.GetChild(0).gameObject;
        GameObject content = background.transform.GetChild(1).gameObject;
        GameObject tier2 = content.transform.GetChild(1).gameObject;
        GameObject abilities = tier2.transform.GetChild(0).gameObject;
        GameObject step = abilities.transform.GetChild(2).gameObject;
        duskShield = step.GetComponent<Skills>();
    }
}
