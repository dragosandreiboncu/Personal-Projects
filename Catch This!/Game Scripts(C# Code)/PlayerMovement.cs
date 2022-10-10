using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class PlayerMovement : Photon.MonoBehaviour
{
    public float movementspeed = 2;
    public PhotonView phView;
    //public int static bombsAvailable = 0;
    public int bombsAvailable = 0;
    public Text playerName;
    public SpriteRenderer sr;
    public int health;
    public static int health_txt;
    private float speedScaling = 0.4f;

    [SerializeField]
    private GameObject bombPrefab;

    Animator animator;

    // Use this for initialization
    void Start()
    {
        animator = GetComponent<Animator>();

        if (phView.isMine || !PhotonNetwork.connected)
        {
            bombsAvailable = 1;
            health = 1;
            health_txt = 1;
        }

        if (phView.isMine)
        {
            GameObject.Find("GameCanvas").transform.Find("HealthShow").GetComponent<showHealth>().localPlayer = this.gameObject;
                //GetComponentInChildren<showHealth>().localPlayer = this.gameObject;
            playerName.text = PhotonNetwork.player.NickName;
        } else
        {
            playerName.text = photonView.owner.NickName;
            playerName.color = Color.cyan;
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (phView.isMine || !PhotonNetwork.connected)
        {
            CheckInput();
        }
    }

    private void CheckInput()
    {
        if (Input.GetKey(KeyCode.A))
        {
            transform.Translate(Vector3.left * movementspeed * Time.deltaTime);
            //sr.flipX = false;
            phView.RPC("FlipFalse", PhotonTargets.All);
            animator.SetBool("IsWalkingSide", true);
        }
        else if (Input.GetKey(KeyCode.D))
        {
            transform.Translate(Vector3.right * movementspeed * Time.deltaTime);
            //sr.flipX = true;
            phView.RPC("FlipTrue", PhotonTargets.All);
            animator.SetBool("IsWalkingSide", true);
        }
        else animator.SetBool("IsWalkingSide", false);

        if (Input.GetKey(KeyCode.W))
        {
            transform.Translate(Vector3.up * movementspeed * Time.deltaTime);
            animator.SetBool("IsWalkingUp", true);
        }
        else animator.SetBool("IsWalkingUp", false);

        if (Input.GetKey(KeyCode.S))
        {
            transform.Translate(Vector3.down * movementspeed * Time.deltaTime);
            animator.SetBool("IsWalkingDown", true);
        }
        else animator.SetBool("IsWalkingDown", false);

        if (Input.GetKeyDown("space") && bombsAvailable > 0)
        {
            //DropBomb(this.gameObject.transform.position);
            phView.RPC("DropBomb", PhotonTargets.All, this.gameObject.transform.position, PhotonNetwork.player.ID);
            //Vector3 bombPosition = this.gameObject.transform.position;
            //PhotonNetwork.Instantiate("Bomb", new Vector3(bombPosition.x, bombPosition.y, 0), Quaternion.identity, 0);
            bombsAvailable--;
            StartCoroutine(AddBomb(1));
        }
    }

    IEnumerator AddBomb(int sec)
    {
        yield return new WaitForSeconds(sec);
        bombsAvailable++;
    }

    [PunRPC]
    void DropBomb(Vector3 bombPosition, int playerId)
    {
        //if (PhotonNetwork.isMasterClient || PhotonNetwork.playerList.Length == 1)
        //{
        //PhotonNetwork.Instantiate(bombPrefab, bombPosition, Quaternion.identity);
        //    PhotonNetwork.Instantiate("Bomb", new Vector3(bombPosition.x, bombPosition.y, 0), Quaternion.identity, 0);
        //}
        GameObject bomb = Instantiate(bombPrefab, bombPosition, Quaternion.identity);
        bomb.GetComponent<Bomb_Explosion>().playerActorId = playerId;
    }

    [PunRPC]
    private void FlipTrue()
    {
        sr.flipX = true;
    }

    public void DecreaseHealth()
    {
        health--;
        health_txt--;
    }

    public void IncreaseHealth()
    {
        if (health == 3)
            return;
        health++;
        health_txt++;
        
    }

    public void MoreBombs()
    {
        bombsAvailable++;
    }

    public void IncreaseSpeed()
    {
        movementspeed += speedScaling;
        animator.speed += speedScaling;
    }

    [PunRPC]
    private void FlipFalse()
    {
        sr.flipX = false;
    }

    public void DestroyPlayer()
    {
        if (photonView.isMine)
        {
            GameObject.Find("GameCanvas").transform.Find("HealthShow").GetComponent<showHealth>().localPlayer = null;
            GameObject.Find("Sounds").GetComponent<PlaySounds>().PlayDeathSound();
            PhotonNetwork.Destroy(this.gameObject);
        }
    }
}
