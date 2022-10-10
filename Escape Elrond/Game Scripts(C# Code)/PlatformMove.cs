using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Threading;
using UnityEngine;

public class PlatformMove : MonoBehaviour
{
    [SerializeField] float moveSpeed = 1f;

    [SerializeField] int returnAfter = 2;

    Rigidbody2D platformRigidBody;

    bool End = true;


    // Start is called before the first frame update
    void Start()
    {
        platformRigidBody = GetComponent<Rigidbody2D>();
        End = false;

    }

    // Update is called once per frame
    void FixedUpdate()
    {
        StartCoroutine(Wait());

    }

    IEnumerator Wait()
    {
        if (!End)
        {
            Right();
            yield return new WaitForSeconds(returnAfter);
            End = true;

        }
        else if (End)
        {
            Left();
            yield return new WaitForSeconds(returnAfter);
            End = false;
        }
    }

    private void Right()
    {
        platformRigidBody.velocity = new Vector2(moveSpeed, 0f);

    }
    private void Left()
    {
        platformRigidBody.velocity = new Vector2(-moveSpeed, 0f);

    }
}
