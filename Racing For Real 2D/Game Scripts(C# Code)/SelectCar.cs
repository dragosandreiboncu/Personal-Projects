using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SelectCar : MonoBehaviour
{
    public GameObject prev;
    public GameObject thisCar;
    public GameObject next;
    void Update()
    {
        if(Input.GetKeyDown(KeyCode.D) && next != null)
        {
            next.SetActive(true);
            thisCar.SetActive(false);
        }
        if(Input.GetKeyDown(KeyCode.A) && prev != null)
        {
            prev.SetActive(true);
            thisCar.SetActive(false);
        }
    }
}
