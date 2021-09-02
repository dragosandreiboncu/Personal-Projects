using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SelectTrack : MonoBehaviour
{
    public GameObject prev;
    public GameObject thisTrack;
    public GameObject next;
    void Update()
    {
        if(Input.GetKeyDown(KeyCode.D) && next != null)
        {
            next.SetActive(true);
            thisTrack.SetActive(false);
        }
        if(Input.GetKeyDown(KeyCode.A) && prev != null)
        {
            prev.SetActive(true);
            thisTrack.SetActive(false);
        }
    }
}
