using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Cinemachine;

public class PlayerMovement : MonoBehaviour
{
    [SerializeField] private LayerMask whatIsEnemy; //StefanEpure

    public CharacterController2D controller;
    public Animator animator;
    public PauseMenu pause;
    public PlayerStats ps;
    [SerializeField] private AudioSource missAttackSound;
    [SerializeField] private AudioSource attackSound;
    [SerializeField] private AudioSource darkSideSound;
    public float runSpeed = 40f;
    public GameObject playerClone;
    private float cloneTime = 7f;
    private float darkSideCooldown = 22f;
    private float darkSideTimer = -22f;
    public bool cloned;
    private Skills darkSide;

    float horizontalMove = 0f;
    bool jump = false;
    bool attack = false;

    void Start()
    {
        GameObject tree = GameObject.Find("Skill_Tree_Canvas(Clone)").transform.GetChild(0).gameObject;
        GameObject background = tree.transform.GetChild(0).gameObject;
        GameObject content = background.transform.GetChild(1).gameObject;
        GameObject tier2 = content.transform.GetChild(1).gameObject;
        GameObject abilities = tier2.transform.GetChild(0).gameObject;
        GameObject step = abilities.transform.GetChild(0).gameObject;
        darkSide = step.GetComponent<Skills>();
        if (playerClone != null)
        {
            playerClone.SetActive(false);
            CharacterController2D playerCloneController = playerClone.GetComponent<CharacterController2D>();
            playerCloneController.clone = true;
        }
        cloned = false;
    }

    /***********************************************/
    /***********************************************/
    //Function for fighting an enemy - by Stefan Epure
    void Attack()
    {
        bool attackedSomebody = false;
        Collider2D[] detectedObjects = Physics2D.OverlapCircleAll(this.gameObject.transform.position, 1, whatIsEnemy);
        //Cel mai bine ar fi sa schimbati raza, eu am pus-o 1, dar vedeti voi care merge mai bine*****^****** Ar merge si parametrizata

        foreach (Collider2D collider in detectedObjects)
        {

            if (collider.gameObject.tag == "Enemy")
            {
                AttackDetails ad;
                ad.damageAmount = ps.attack;
                ad.position = (Vector2)collider.gameObject.transform.position;
                ad.stunDamageAmount = 5;
                if (!collider.gameObject.transform.parent.GetComponent<Entity>().isDead)
                {
                    collider.gameObject.transform.parent.GetComponent<Entity>().Damage(ad);
                    attackedSomebody = true;
                }
            }

        }
        if (attackedSomebody)
        {
            attackSound.Play();
        } else
        {
            if (!missAttackSound.isPlaying)
            {
                missAttackSound.Play();
            }
        }
    }
    /**************************************************/
    /**************************************************/


    // Update is called once per frame
    void Update()
    {
        if (pause.GameIsPaused == false)
        {
            if (!cloned)
            {
                if (ps.treeIsUp == false)
                {
                    if (Input.GetButtonDown("Attack1") && !attack)
                    {
                        animator.SetTrigger("Attack1");
                        Attack();
                    }
                    attack = animator.GetBool("isAttacking");
                }
                horizontalMove = Input.GetAxisRaw("Horizontal") * runSpeed;

                animator.SetFloat("Speed", Mathf.Abs(horizontalMove));

                if (Input.GetButtonDown("Jump") && !attack)
                {
                    animator.SetTrigger("Jump");
                    jump = true;
                }
            }
            // DarkSide skill
            if ((Input.GetKeyDown("[3]") || Input.GetKeyDown(KeyCode.Alpha3)) &&
                    Time.time > darkSideTimer + darkSideCooldown && this.transform != playerClone.transform && darkSide.skillAvailable)
            {
                darkSideSound.Play();
                darkSideTimer = Time.time;
                playerClone.transform.position = GameObject.FindGameObjectWithTag("Player").transform.position;
                playerClone.SetActive(true);
                cloned = true;
                // Seteaza animatia de idle playerului original
                horizontalMove = 0;
                animator.SetFloat("Speed", Mathf.Abs(horizontalMove));
                StartCoroutine(DarkSide());
            }
            if (playerClone != null && !playerClone.activeSelf)
            {
                cloned = false;
            }
        }

    }

    private void FixedUpdate()
    {
        // Move our character
        if (!attack)
        {
            controller.Move(horizontalMove * Time.fixedDeltaTime, false, jump);
            jump = false;
        } else
        {
            controller.Move(0, false, false);
        }
    }

    IEnumerator DarkSide()
    {
        // Pentru 7 secunde clona va fi activa apoi devine inactiva
        yield return new WaitForSeconds(cloneTime);
        playerClone.SetActive(false);
    }
}
