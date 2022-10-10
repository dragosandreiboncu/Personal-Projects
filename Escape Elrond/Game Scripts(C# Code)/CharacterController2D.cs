using UnityEngine;
using UnityEngine.Events;

public class CharacterController2D : MonoBehaviour
{
    [SerializeField] private float m_SecondJump = 14f;                          // for second jump
    [SerializeField] private float m_JumpForce = 400f;							// Amount of force added when the player jumps.
	[Range(0, 1)] [SerializeField] private float m_CrouchSpeed = .36f;			// Amount of maxSpeed applied to crouching movement. 1 = 100%
	[Range(0, .3f)] [SerializeField] private float m_MovementSmoothing = .05f;	// How much to smooth out the movement
	[SerializeField] private bool m_AirControl = true;							// Whether or not a player can steer while jumping;
	[SerializeField] private LayerMask m_WhatIsGround;							// A mask determining what is ground to the character
	[SerializeField] private Transform m_GroundCheck;							// A position marking where to check if the player is grounded.
	[SerializeField] private Transform m_CeilingCheck;							// A position marking where to check for ceilings
	[SerializeField] private Collider2D m_CrouchDisableCollider;				// A collider that will be disabled when crouching
	[SerializeField] private Animator animator;
    [SerializeField] private AudioSource jumpSound;
    [SerializeField] private AudioSource landSound;
    [SerializeField] private AudioSource walkSound;
    [SerializeField] private AudioSource shadowStepSound;

    const float k_GroundedRadius = .2f; // Radius of the overlap circle to determine if grounded
	private bool m_Grounded;            // Whether or not the player is grounded.
	const float k_CeilingRadius = .2f; // Radius of the overlap circle to determine if the player can stand up
	private Rigidbody2D m_Rigidbody2D;
	private bool m_FacingRight = true;  // For determining which way the player is currently facing.
	private Vector3 m_Velocity = Vector3.zero;
    private Skills shadowStep;
    public bool clone = false;

	[Header("Events")]
	[Space]

	public UnityEvent OnLandEvent;
	[System.Serializable]
	public class BoolEvent : UnityEvent<bool> { }

	public BoolEvent OnCrouchEvent;
	private bool m_wasCrouching = false;

    public bool doubleJumpEnabled = true;   // variable for double jump, when you unlock this skill this variable is true
    private bool canDoubleJump = true;   // if he can double jump

    void Start()
    {
        GameObject tree = GameObject.Find("Skill_Tree_Canvas(Clone)").transform.GetChild(0).gameObject;
        GameObject background = tree.transform.GetChild(0).gameObject;
        GameObject content = background.transform.GetChild(1).gameObject;
        GameObject tier2 = content.transform.GetChild(1).gameObject;
        GameObject abilities = tier2.transform.GetChild(0).gameObject;
        GameObject step = abilities.transform.GetChild(1).gameObject;
        shadowStep = step.GetComponent<Skills>();
    }
    private void Awake()
	{
		m_Rigidbody2D = GetComponent<Rigidbody2D>();

		if (OnLandEvent == null)
			OnLandEvent = new UnityEvent();

		if (OnCrouchEvent == null)
			OnCrouchEvent = new BoolEvent();
	}

	private void FixedUpdate()
	{
        bool playedOnce = false;
		bool wasGrounded = m_Grounded;
		m_Grounded = false;

        // The player is grounded if a circlecast to the groundcheck position hits anything designated as ground
        // This can be done using layers instead but Sample Assets will not overwrite your project settings.

        Collider2D[] colliders = Physics2D.OverlapCircleAll(m_GroundCheck.position, k_GroundedRadius, m_WhatIsGround);
		for (int i = 0; i < colliders.Length; i++)
		{
			if (colliders[i].gameObject != gameObject)
			{
                if (!playedOnce && !wasGrounded && !landSound.isPlaying)
                {
                    landSound.Play();
                    playedOnce = true;
                }
                animator.SetBool("isGrounded", true);
				m_Grounded = true;
				if (!wasGrounded)
					OnLandEvent.Invoke();
			}
		}
	}


	public void Move(float move, bool crouch, bool jump)
	{
		// If crouching, check to see if the character can stand up
		if (!crouch)
		{
			// If the character has a ceiling preventing them from standing up, keep them crouching
			if (Physics2D.OverlapCircle(m_CeilingCheck.position, k_CeilingRadius, m_WhatIsGround))
			{
				crouch = true;
			}
		}

		//only control the player if grounded or airControl is turned on

		// Move the character by finding the target velocity
		Vector3 targetVelocity = new Vector2(move * 10f, m_Rigidbody2D.velocity.y);
		// And then smoothing it out and applying it to the character
		m_Rigidbody2D.velocity = Vector3.SmoothDamp(m_Rigidbody2D.velocity, targetVelocity, ref m_Velocity, m_MovementSmoothing);
    
        if (m_Grounded && Mathf.Abs(move) > 0.1 && !walkSound.isPlaying)
        {
            walkSound.Play();
        }
        if (!m_Grounded || Mathf.Abs(move) <= 0.1)
        {
            walkSound.Stop();
        }
		// If the input is moving the player right and the player is facing left...
		if (move > 0 && !m_FacingRight)
		{
			// ... flip the player.
			Flip();
		}
		// Otherwise if the input is moving the player left and the player is facing right...
		else if (move < 0 && m_FacingRight)
		{
			// ... flip the player.
			Flip();
		}
    	// If the player should jump...
		if (m_Grounded && jump && !shadowStep.skillAvailable)
		{
            // Add a vertical force to the player.
            jumpSound.Play();
            animator.SetBool("isGrounded", false);
			m_Grounded = false;
			m_Rigidbody2D.AddForce(new Vector2(0f, m_JumpForce));
		}

        if (shadowStep.skillAvailable)
        {
            if (m_Grounded)
            {
                canDoubleJump = true;
            }
            if (m_Grounded && jump)
            {   //first jump
                jumpSound.Play();
                animator.SetBool("isGrounded", false);
                m_Grounded = false;
                m_Rigidbody2D.AddForce(new Vector2(0f, m_JumpForce));
            }
            else if (canDoubleJump && jump && !clone)
            {    //second jump
                shadowStepSound.Play();
                animator.SetBool("isGrounded", false);
                m_Rigidbody2D.velocity = new Vector2(0f, m_SecondJump);
                canDoubleJump = false;
            }
        }
    }


	private void Flip()
	{
		// Switch the way the player is labelled as facing.
		m_FacingRight = !m_FacingRight;

		// Multiply the player's x local scale by -1.
		Vector3 theScale = transform.localScale;
		theScale.x *= -1;
		transform.localScale = theScale;
	}
}
