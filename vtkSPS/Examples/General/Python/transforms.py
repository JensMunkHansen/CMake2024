import numpy as np
import vtk

def create_translation_matrix(tx, ty, tz):
    return np.array([
        [1, 0, 0, tx],
        [0, 1, 0, ty],
        [0, 0, 1, tz],
        [0, 0, 0,  1]
    ])

def create_rotation_matrix_z(theta):
    cos_t = np.cos(theta)
    sin_t = np.sin(theta)
    return np.array([
        [ cos_t, -sin_t, 0, 0],
        [ sin_t,  cos_t, 0, 0],
        [    0,      0, 1, 0],
        [    0,      0, 0, 1]
    ])

def create_rotation_matrix_y(theta):
    cos_t = np.cos(theta)
    sin_t = np.sin(theta)
    return np.array([
        [ cos_t,  0, sin_t, 0],
        [     0,  1,     0, 0],
        [-sin_t,  0, cos_t, 0],
        [     0,  0,     0, 1]
    ])

# Define three transformations: Translation (T1), Rotation around Z-axis (T2), Rotation around Y-axis (T3)
T1 = create_translation_matrix(1, 2, 3)               # Translation
T2 = create_rotation_matrix_z(np.pi / 4)              # 45-degree rotation around Z-axis
T3 = create_rotation_matrix_y(np.pi / 6)              # 30-degree rotation around Y-axis

# Concatenation: Intrinsic (order T1 * T2 * T3)
intrinsic_concat = T1 @ T2 @ T3

# Concatenation: Extrinsic (order T3 * T2 * T1)
extrinsic_concat = T3 @ T2 @ T1

print("Intrinsic Concatenation:\n", intrinsic_concat)
print("Extrinsic Concatenation:\n", extrinsic_concat)

# Create vtkTransforms for translation, rotation around Z, and rotation around Y
T1_vtk = vtk.vtkTransform()
T1_vtk.Translate(1, 2, 3)  # Translation

T2_vtk = vtk.vtkTransform()
T2_vtk.RotateZ(45)  # 45-degree rotation around Z-axis

T3_vtk = vtk.vtkTransform()
T3_vtk.RotateY(30)  # 30-degree rotation around Y-axis

# Create the final transform and set PreMultiply mode (extrinsic transformations)
finalTransform_pre = vtk.vtkTransform()
finalTransform_pre.PreMultiply()

# Apply transformations in the extrinsic order: T1 * T2 * T3
finalTransform_pre.Concatenate(T1_vtk)
finalTransform_pre.Concatenate(T2_vtk)
finalTransform_pre.Concatenate(T3_vtk)

print("PreMultiply Transform Matrix (T1 * T2 * T3):\n", finalTransform_pre.GetMatrix())

finalTransform_post = vtk.vtkTransform()
finalTransform_post.PostMultiply()

# Apply transformations in the extrinsic order: T1 * T2 * T3
finalTransform_post.Concatenate(T1_vtk)
finalTransform_post.Concatenate(T2_vtk)
finalTransform_post.Concatenate(T3_vtk)

print("PostMultiply Transform Matrix (T1 * T2 * T3):\n", finalTransform_post.GetMatrix())


import vtk

# Create a vtkTransform and enable PostMultiply mode
stackedTransform = vtk.vtkTransform()
stackedTransform.PostMultiply()

# Push the identity transform onto the stack first
stackedTransform.Identity()  # Set to identity transform
stackedTransform.Push()  # Push the identity onto the stack

# Apply transformations one by one and push them onto the stack
stackedTransform.Translate(1, 2, 3)  # Apply T1 (translation)
stackedTransform.Push()  # Save T1 on the stack

stackedTransform.RotateZ(45)  # Apply T2 (rotation around Z)
stackedTransform.Push()  # Save T1 * T2 on the stack

stackedTransform.RotateY(30)  # Apply T3 (rotation around Y)
stackedTransform.Push()  # Save T1 * T2 * T3 on the stack

# Dummy Pop: Still returns the full transformation (T1 * T2 * T3)
stackedTransform.Pop()  # Pop the last push, but still gives full transformation
print("Full Transform (T1 * T2 * T3 after dummy pop):\n", stackedTransform.GetMatrix())

# Now pop the transformations off the stack one by one
stackedTransform.Pop()  # Remove T3, we're back to T1 * T2
print("After Popping T3 (T1 * T2):\n", stackedTransform.GetMatrix())

stackedTransform.Pop()  # Remove T2, we're back to T1
print("After Popping T2 (T1):\n", stackedTransform.GetMatrix())

stackedTransform.Pop()  # Remove T1, back to Identity
print("After Popping T1 (Identity):\n", stackedTransform.GetMatrix())
