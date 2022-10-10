using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class showHealth : MonoBehaviour
{
    private string symbol;
    public GameObject localPlayer;
    void Start()
    {
        symbol = gameObject.GetComponent<UnityEngine.UI.Text>().text;
    }
    void Update()
    {
        if (localPlayer != null)
            gameObject.GetComponent<UnityEngine.UI.Text>().text = symbol + localPlayer.GetComponent<PlayerMovement>().health;
        else
            gameObject.GetComponent<UnityEngine.UI.Text>().text = symbol + 0;
    }
}
