![image-20231218202421626](/Users/lyk/Library/Application Support/typora-user-images/image-20231218202421626.png)

https://ubuntu.com/server/docs/nvidia-drivers-installation



https://docs.nvidia.com/cuda/cuda-installation-guide-microsoft-windows/index.html?highlight=conda#conda-overview





# ["pip install gym" failing with "python setup.py egg_info did not run successfully" errors?](https://stackoverflow.com/questions/76129688/why-is-pip-install-gym-failing-with-python-setup-py-egg-info-did-not-run-succ)

Error output maybe

```text
...
wheel.vendored.packaging.requirements.InvalidRequirement: Expected end or semicolon (after version specifier)
opencv-python>=3.
```

Or

```text
  × python setup.py egg_info did not run successfully.
  │ exit code: 1
  ╰─> [1 lines of output]
      error in gym setup command: 'extras_require' must be a dictionary whose values are strings or lists of strings containing valid project/version requirement specifiers.
      [end of output]
```



One workaround that you can find in [Github issue #3211](https://github.com/openai/gym/issues/3211) is to downgrade the versions of setuptools and wheel, as in:

```py
!pip install setuptools==65.5.0 "wheel<0.40.0"
```

[->Source](https://stackoverflow.com/questions/76129688/why-is-pip-install-gym-failing-with-python-setup-py-egg-info-did-not-run-succ)



[`Building wheel for opencv-python (PEP 517) ... -` runs forever](https://stackoverflow.com/questions/63669752/building-wheel-for-opencv-python-pep-517-runs-forever)



```
pip3 install opencv-python==4.1.2.30
```

[->Source](https://www.reddit.com/r/learnpython/comments/s618zp/error_could_not_build_wheels_for_opencvpython/)