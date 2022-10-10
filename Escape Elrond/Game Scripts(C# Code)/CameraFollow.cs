using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraFollow : MonoBehaviour
{
    private Transform playerTransform;
    public GameObject playerCamera;
    public GameObject cloneCamera;
    public GameObject playerClone;

    // Start is called before the first frame update
    void Start()
    {
        playerTransform = GameObject.FindGameObjectWithTag("Player").transform;
        playerCamera.SetActive(true);
        cloneCamera.SetActive(false);
    }

    // Update is called once per frame
    void LateUpdate()
    {
        if(playerClone.activeSelf)
        {
            playerCamera.SetActive(false);
            cloneCamera.SetActive(true);
        }
        else
        {
            playerCamera.SetActive(true);
            cloneCamera.SetActive(false);
        }
        /*Vector3 t = transform.position;

        // Case 1
        if (playerTransform.position.x <= 1.55f && playerTransform.position.x >= -1.4f)
        {
            t.x = playerTransform.position.x;

        }

        if (playerTransform.position.y >= -0.1f && playerTransform.position.y <= 25f && playerTransform.position.x <= 7f)
        {
            t.y = playerTransform.position.y;
        }

        // Case 2

        if (playerTransform.position.x <= 19.5f && playerTransform.position.x >= -1.4f
            && playerTransform.position.y >= 18.5f)
        {
            t.x = playerTransform.position.x;

        }

        if (playerTransform.position.y >= 21.6f && playerTransform.position.y <= 24.8f)
        {
            t.y = playerTransform.position.y;
        }

        transform.position = t;*/

    }


}