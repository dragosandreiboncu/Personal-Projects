using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Lava : MonoBehaviour
{
    private bool isTriggered;

    void Start()
    {
        isTriggered = false;
    }

    void OnTriggerEnter2D(Collider2D col)
    {
        if (col.gameObject.tag == "Player" && isTriggered == false)
        {
            isTriggered = true;
            col.gameObject.GetComponent<PlayerMovement>().DecreaseHealth();

            if (col.gameObject.GetComponent<PlayerMovement>().health < 1)
                col.gameObject.GetComponent<PlayerMovement>().DestroyPlayer();

            StartCoroutine(TrapReactivate(1));
        }

    }
    
    IEnumerator TrapReactivate(int sec)
    {
        yield return new WaitForSeconds(sec);
        isTriggered = false;
    }
}
