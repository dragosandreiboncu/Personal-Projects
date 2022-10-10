using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoreHealth : MonoBehaviour
{
    void OnTriggerEnter2D(Collider2D col)
    {
        if (col.gameObject.tag == "Player")
        {
            GameObject.Find("Sounds").GetComponent<PlaySounds>().PlayPickupSound();
            col.gameObject.GetComponent<PlayerMovement>().IncreaseHealth();
            Debug.Log("Bau");
            Destroy(this.gameObject);
        }

    }
}
