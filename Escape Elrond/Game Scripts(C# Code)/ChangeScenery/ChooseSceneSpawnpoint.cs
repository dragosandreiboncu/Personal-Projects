using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChooseSceneSpawnpoint : MonoBehaviour
{
    public string nextDoor = null;

    void Awake()
    {
        DontDestroyOnLoad(this.gameObject);
    }
}
