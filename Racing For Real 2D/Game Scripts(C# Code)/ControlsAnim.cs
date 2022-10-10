using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ControlsAnim : MonoBehaviour
{
    public GameObject menu1;
    public GameObject menu2;
    private float distance;
    private bool direction;
    // Start is called before the first frame update
    void Start()
    {
        distance = 0;
        direction = true;
        Vector3 newpos1 = new Vector3(menu1.transform.position.x - 40f, menu1.transform.position.y - 20f, menu1.transform.position.z);
        Vector3 newpos2 = new Vector3(menu2.transform.position.x - 40f, menu2.transform.position.y + 20f, menu2.transform.position.z);
        menu1.transform.position = newpos1;
        menu2.transform.position = newpos2;
    }

    // Update is called once per frame
    void Update()
    {
        distance += 0.01f;
        if(direction)
        {
            Vector3 newpos1 = new Vector3(menu1.transform.position.x + 0.1f, menu1.transform.position.y + 0.05f, menu1.transform.position.z);
            Vector3 newpos2 = new Vector3(menu2.transform.position.x + 0.1f, menu2.transform.position.y - 0.05f, menu2.transform.position.z);
            menu1.transform.position = newpos1;
            menu2.transform.position = newpos2;
        }
        else
        {
            Vector3 newpos1 = new Vector3(menu1.transform.position.x - 0.1f, menu1.transform.position.y - 0.05f, menu1.transform.position.z);
            Vector3 newpos2 = new Vector3(menu2.transform.position.x - 0.1f, menu2.transform.position.y + 0.05f, menu2.transform.position.z);
            menu1.transform.position = newpos1;
            menu2.transform.position = newpos2;
        }
        if(distance >= 8)
        {
            direction = !direction;
            distance = 0;
        }
    }
}
