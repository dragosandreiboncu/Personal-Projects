using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Traps : MonoBehaviour
{

    Animator animator;
    private bool isTriggered;
    public PhotonView phView;

    void Start()
    {
       animator = GetComponent<Animator>();
       isTriggered = false;
    }

    void OnTriggerEnter2D(Collider2D col)
    {
        if (col.gameObject.tag == "Player" && isTriggered == false)
        {
            //animator.SetBool("activate", true);
            //isTriggered = true;
            col.gameObject.GetComponent<PlayerMovement>().DecreaseHealth();
            
            if (col.gameObject.GetComponent<PlayerMovement>().health < 1)
                col.gameObject.GetComponent<PlayerMovement>().DestroyPlayer();

            //StartCoroutine(TrapReactivate(1));
            phView.RPC("TriggerTrapAnimation", PhotonTargets.All);

        }

    }
    
    [PunRPC]
    public void TriggerTrapAnimation()
    {
        animator.SetBool("activate", true);
        isTriggered = true;

        StartCoroutine(TrapReactivate(1));
    }
    IEnumerator TrapReactivate(float sec)
    {
        yield return new WaitForSeconds(sec);
        animator.SetBool("activate", false);
        isTriggered = false;
    }
}
