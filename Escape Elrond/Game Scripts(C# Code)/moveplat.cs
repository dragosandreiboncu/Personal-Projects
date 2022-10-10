
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.Resources;
using UnityEngine;

public class moveplat : MonoBehaviour
{
    
    public float speed = 1;
    public float duration = 12;
    private float timeLeft;

    void Start()
    {
        timeLeft = duration;
    }

    void Update()
    {


        if (timeLeft > -duration)
        {
            timeLeft -= Time.deltaTime;
            if (timeLeft > 0)
                transform.Translate(Vector2.down * speed * Time.deltaTime);
            else
                if (timeLeft < 0)
                transform.Translate(Vector2.up * speed * Time.deltaTime);

        }
        else timeLeft = duration;

        
       
    }
}