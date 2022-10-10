using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoreBombs : MonoBehaviour
{
    void OnTriggerEnter2D(Collider2D col)
    {
        if(col.gameObject.tag == "Player")
        {
            GameObject.Find("Sounds").GetComponent<PlaySounds>().PlayPickupSound();
            col.gameObject.GetComponent<PlayerMovement>().MoreBombs();
            Debug.Log("Speram");
            Destroy(this.gameObject);
        }
        
    }
}
