using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SetPlayerPosition : MonoBehaviour
{
    void Start()
    {
        string nextDoor = GameObject.Find("SceneManagerDontDestroy(Clone)").GetComponent<SaveInfoForNextLevel>().nextDoor;
        GameObject doorToTeleport = GameObject.Find(nextDoor);
        if (doorToTeleport != null)
        {
            transform.position = doorToTeleport.transform.position;
        }
    }
}
