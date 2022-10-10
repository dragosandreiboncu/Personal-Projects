using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LoadingScreen : MonoBehaviour
{
    private float countdown;
    public GameObject health;
    public GameObject loadingscreen;
    void Start()
    {
        countdown = 2f;
    }

    void Update()
    {
        if (countdown <= 0)
        {
            health.SetActive(true);
            loadingscreen.SetActive(false);
        }
        else
            countdown -= Time.deltaTime;
    }
}
