from setuptools import find_packages, setup

package_name = 'banana'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='mohzak',
    maintainer_email='kokoriquaye@gmail.com',
    description='Webcam reader',
    license='Apache License 2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            "webcam_driver_pub = banana.webcam_driver_pub:main",
            "webcam_driver_sub = banana.webcam_driver_sub:main"
        ],
    },
)
