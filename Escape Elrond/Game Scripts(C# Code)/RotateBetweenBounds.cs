using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RotateBetweenBounds : MonoBehaviour
{


    public float k1 = 3f;
    public float k2 = 2f;
    public float k3 = 26f;
    private float currentTime = 0f;

    // Start is called before the first frame update
    void Start()
    {
        transform.rotation = Quaternion.identity;
    }

    // Update is called once per frame
    void Update()
    {
        currentTime += Time.deltaTime;
        transform.eulerAngles = new Vector3 (0, 0, k1 * Mathf.Cos(k2 * currentTime) - k3);
    }
}
