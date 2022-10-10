using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CloneStats : MonoBehaviour
{
    private int life;
    int attack = 20;
    // Start is called before the first frame update
    void Start()
    {
        life = 1;
    }
    // Update is called once per frame
    void Update()
    {
        if (life <= 0)
        {
            this.gameObject.SetActive(false);
            life = 1;
        }
    }

    public void TakeDamage(int damage)
    {
        life -= damage;
    }
}

